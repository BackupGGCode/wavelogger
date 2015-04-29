The build system provides a lot of functionality.  The following are some of the commands that can be used in the [CPUDisc](CPUDisc.md) and PowerDisc directories.

  * `gmake`
> > This builds the firmware in its default release mode.

  * `gmake debug`
> > This builds the firmware in its debug mode.  This adds size to the resulting firmware
> > but it makes it much more debuggable.

  * `gmake write`
> > This builds and writes the firmware to the device using an AVRISPMKII in circuit
> > programmer.  The main CPU board has a six pin header.  The power supply board requires
> > either a custom adapter, or individual test clamps for each signal.

  * `gmake write debug`
> > This is the same as write, but it writes a debug version of the firmware.

  * `gmake write_fuses`
> > This writes the fuse values from the firmware to the device fuses.  This is needed to
> > correctly configure the device, but is only needed once, unless the fuses change
> > during development.

  * `gmake show_fuses`
> > This shows the current state of the fuses.  It can be useful to to verify that
> > write\_fuses performed correctly.