# clipped

clipped monitors the ownership of the primary and clipboard X11 selections.
When ownership changes, the name of the selection that changed is printed.

It also provides the `clipsync` script to synchronize content between the
primary and clipboard selections using `xsel`.

## Packages

* **RPM** package available from [copr][1]. [![Copr build status](https://copr.fedorainfracloud.org/coprs/jcrd/clipped/package/clipped/status_image/last_build.png)](https://copr.fedorainfracloud.org/coprs/jcrd/clipped/package/clipped/)

  Install with:
  ```
  dnf copr enable jcrd/clipped
  dnf install clipped
  ```

## Usage

```
usage: clipped [options]

options:
  -h            Show help message
  -s SELECTION  Monitor this selection
  -v            Show version
```

### clipsync

Enable the systemd service to run when the `graphical-session.target` is
reached:
```
systemctl --user enable clipsync
```

## License

This project is licensed under the MIT License (see [LICENSE](LICENSE)).

## Acknowledgements

* Inspired by [clipnotify](https://github.com/cdown/clipnotify)

[1]: https://copr.fedorainfracloud.org/coprs/jcrd/clipped/
