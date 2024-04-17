FROM ubuntu:22.04

RUN apt update -yq \
    && apt upgrade -yq \
    && apt install -yq build-essential git curl python3 python3-pip python3-venv

RUN curl -fSL -A "Mozilla/4.0" -o /tmp/xc8.run "https://ww1.microchip.com/downloads/aemDocuments/documents/DEV/ProductDocuments/SoftwareTools/xc8-v2.46-full-install-linux-x64-installer.run" \
    && chmod a+x /tmp/xc8.run \
    && /tmp/xc8.run --mode unattended --unattendedmodeui none \
        --netservername localhost --LicenseType FreeMode --prefix /opt/microchip/xc8 \
    && rm /tmp/xc8.run

ENV PATH $PATH:/opt/microchip/xc8/bin