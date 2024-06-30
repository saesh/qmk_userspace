# QMK Userspace

Open this repository in VS Code and start the dev container `QMK CLI`. Inside the dev container shell
procede to compile and flash.

Compile firmwares defined in `qmk.json`

```
qmk userspace-compile
```

Compile specific firmware

```
qmk compile -kb evyd13/plain60 -km saesh
```

Flash specific firmware

```
qmk flash -kb evyd13/plain60 -km saesh
```
