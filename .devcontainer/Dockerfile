FROM ubuntu:22.04

RUN apt update -yq \
    && apt upgrade -yq \
    && apt install -yq \
    build-essential \
    git \
    curl \
    python3 \
    python3-pip \
    python3-venv \
    clang-format \
    gperf

RUN curl -fSL -A "Mozilla/4.0" -o /tmp/xc8.run "https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v2.46-full-install-linux-x64-installer.run" \
    && chmod a+x /tmp/xc8.run \
    && /tmp/xc8.run --mode unattended --unattendedmodeui none \
        --netservername localhost --LicenseType FreeMode --prefix /opt/microchip/xc8 \
    && rm /tmp/xc8.run

ENV PATH $PATH:/opt/microchip/xc8/bin

RUN curl -fSL \
    -A "Mozilla/4.0" \
    -e "https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide" \
    -o /tmp/mplabx-installer.tar \
    "https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/MPLABX-v6.20-linux-installer.tar" \
    && tar xf /tmp/mplabx-installer.tar && rm /tmp/mplabx-installer.tar
RUN apt install -yq libusb-1.0-0-dev
RUN USER=root ./*-installer.sh --nox11 -- --unattendedmodeui none --mode unattended --installdir /opt/microchip/mplabx \
    && rm ./*-installer.sh

ENV PATH $PATH:/opt/microchip/mplabx/mplab_ide/bin
ENV PATH $PATH:/opt/microchip/mplabx/mplab_platform/mplab_ipe

RUN sed -i 's/\. \.\./\. $mplabx_dir/g' /opt/microchip/mplabx/mplab_platform/mplab_ipe/ipecmd.sh