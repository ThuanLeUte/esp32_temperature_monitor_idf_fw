# VM setting for IDF platform (Ubuntu 18.04.6)

## I. Steps for machine setup:

1. **Setup open SSH**

   https://linuxize.com/post/how-to-enable-ssh-on-ubuntu-18-04/

2. **Get IP address**

   ifconfig -> sudo apt install net-tools

3. **Connect SSH by VScode**

4. **Git install: sudo apt install git**

5. **Copy cert for GitHub**



## II. Steps for IDF setup

1. **Clone project at: https://github.com/ThuanLeUte/esp32-temperature-monitor-idf-fw**

2. **Git submodule setup:**

   Create folder sdk and go to sdk by: cd sdk

   git submodule init

   git submodule add https://github.com/espressif/esp-idf

   git checkout v4.3

   git submodule update --recursive

3. **Run setup.sh**

   ./setup.sh

4. **Build, flash and log monitor:**

   Go to app directory  execute following command:

   make -j4 flash monitor


## **Note:** Guide how to fix the following issue

CONFIG_MBEDTLS_CERTIFICATE_BUNDLE=n

https://github.com/espressif/esp-idf/issues/7631

