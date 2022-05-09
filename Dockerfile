FROM ubuntu:20.04

# Install packages
RUN apt-get update && \
    apt-get install -y gcc make vim unzip man-db manpages-posix manpages-dev manpages-posix-dev && \
    yes | unminimize && \
    apt-get clean
