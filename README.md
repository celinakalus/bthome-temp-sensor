# BTHome temperature sensor

A [BTHome](https://bthome.io/) temperature sensor based on [Zephyr RTOS](https://www.zephyrproject.org/).

## Building

To build the application for some board `<BOARD>` with west, clone the repo anywhere, enter the repository root, and do the following:

```shell
$ west build -b <BOARD> .
```

Make sure you have followed the [Getting Started Guide](https://docs.zephyrproject.org/latest/develop/getting_started/index.html) for Zephyr first and you have the python venv and the Zephyr environment variables set accordingly. 
