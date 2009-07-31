/*
 * Copyright 2009 Anton Staaf
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "process/wavefile.h"

using namespace Err;
using namespace Data;
using namespace Files;

/**********************************************************************************************************************/
Block::Block() :
    _offset(0),
    _type(invalid),
    _ticks(0)
{
}
/**********************************************************************************************************************/
Error Block::read(int file)
{
    ssize_t	length;

    CheckP(length  = ::read(file, _buffer, 512));
    CheckP(_offset = lseek(file, 0, SEEK_CUR));

    _offset -= 512;
    _type    = data;
    _ticks   = 0;

    if (length != 512)
    {
	if (length == 0)
	    _type = eof;
	else
	    _type = invalid;

	return success;
    }

    {
	uint32	sum = 0;

	for (int i = 0; i < 512; ++i)
	    sum += _buffer[i];

	if (sum == 0)
	{
	    _type = empty;
	    return success;
	}
    }

    switch (_data.type)
    {
	case 0x00: _type = header;  break;
	case 0x01: _type = data;    break;
	default:   _type = invalid; break;
    }

    if (_type == data)
	_ticks = _data.rtc_ticks;

    return success;
}
/**********************************************************************************************************************/
off_t Block::offset()
{
    return _offset;
}
/**********************************************************************************************************************/
Block::Type Block::type()
{
    return _type;
}
/**********************************************************************************************************************/
uint64 Block::ticks()
{
    return _ticks;
}
/**********************************************************************************************************************/
uint16 Block::sample(int tick, int channel)
{
    if (_type != data)
	return 0;

    const AnalogSample	&sample = _data.sample[tick >> 1];

    switch (channel)
    {
	case 0:
	    if ((tick & 1) == 0)
		return sample.data[1] | ((sample.data[0] & 0xc0) << 2);
	    else
		return sample.data[3] | ((sample.data[0] & 0x0c) << 6);

	case 1:
	    if ((tick & 1) == 0)
		return sample.data[2] | ((sample.data[0] & 0x30) << 4);
	    else
		return sample.data[4] | ((sample.data[0] & 0x03) << 8);

	default:
	    return 0;
    }
}
/**********************************************************************************************************************/
Sequence::Sequence() :
    _start(uint64(-1)),
    _stop(uint64(-1)),
    _length(0)
{
}
/**********************************************************************************************************************/
Error Sequence::add_block(Block *block)
{
    uint64	ticks = block->ticks();

    if (_start == uint64(-1))
	_start = ticks;

    _stop    = ticks + 200;
    _length += 512;

    return success;
}
/**********************************************************************************************************************/
uint32 Sequence::length()
{
    return _length;
}
/**********************************************************************************************************************/
void Sequence::debug_print(int indent)
{
    int64	delta = _stop - _start;
    float	hours = float(delta) / float(100 * 60 * 60);

    printf("%*sSequence\n",                indent, "");
    printf("%*s    start....: 0x%08llx\n", indent, "", _start);
    printf("%*s    stop.....: 0x%08llx\n", indent, "", _stop);
    printf("%*s    hours....: %0.2f\n",    indent, "", hours);
}
/**********************************************************************************************************************/
Segment::Segment(Block *header) :
    _offset(header->offset()),
    _length(0)
{
}
/**********************************************************************************************************************/
Error Segment::add_sequence(Sequence *sequence)
{
    _sequences.append(sequence);
    _length += sequence->length();

    return success;
}
/**********************************************************************************************************************/
void Segment::debug_print(int indent)
{
    printf("%*sSegment\n",                 indent, "");
    printf("%*s    offset...: 0x%08llx\n", indent, "", (int64)_offset);
    printf("%*s    length...: 0x%08x\n",   indent, "", _length);

    for (uint i = 0; i < _sequences.length(); ++i)
	_sequences[i]->debug_print(indent + 4);
}
/**********************************************************************************************************************/
Wavefile::Wavefile() :
    _block(new Block()),
    _old_block(new Block()),
    _file(-1),
    _callback(null)
{
}
/**********************************************************************************************************************/
Error Wavefile::read(Path path, ProcessBlockCallback callback)
{
    const char	*filename = path.get().str();

    _callback = callback;

    CheckStringP(_file = open(filename, O_RDONLY), "Failed to open file %s", filename);

    Check(match(Block::invalid));

    while (_block->type() != Block::eof)
	Check(read_segment());

    return success;
}
/**********************************************************************************************************************/
Error Wavefile::read_segment()
{
    printf("Reading segment  at 0x%08llx\n", (int64)_block->offset());

    match(Block::header);

    Segment	*segment = new Segment(_old_block);

    while (_block->type() == Block::data)
	Check(read_sequence(segment));

    _segments.append(segment);

    return success;
}
/**********************************************************************************************************************/
Error Wavefile::read_sequence(Segment *segment)
{
    printf("Reading sequence at 0x%08llx (0x%08llx)\n", (int64)_block->offset(), _block->ticks());

    uint64	ticks     = uint64(-1);
    Sequence	*sequence = new Sequence();

    while (_block->type() == Block::data)
    {
	if (ticks != uint64(-1) && abs(_block->ticks() - _old_block->ticks() - 200) > 20)
	    break;

	Check(match(Block::data));

	ticks = _old_block->ticks();

	Check(sequence->add_block(_old_block));
    }

    Check(segment->add_sequence(sequence));

    return success;
}
/**********************************************************************************************************************/
Error Wavefile::match(const Block::Type type)
{
    CheckStringB(type == _block->type(), "Missmatched block type %d != %d", type, _block->type());

    swap(_block, _old_block);

    do
    {
	_block->read(_file);
    }
    while (_block->type() == Block::empty);

    if (_callback)
	_callback(_block);

    return success;
}
/**********************************************************************************************************************/
void Wavefile::debug_print(int indent)
{
    printf("%*sWavefile\n",              indent, "");

    for (uint i = 0; i < _segments.length(); ++i)
	_segments[i]->debug_print(indent + 4);
}
/**********************************************************************************************************************/
