# Use phusion/baseimage as base image. To make your builds
# reproducible, make sure you lock down to a specific version, not
# to `latest`! See
# https://github.com/phusion/baseimage-docker/blob/master/Changelog.md
# for a list of version numbers.
FROM phusion/baseimage:jammy-1.0.1

# Use baseimage-docker's init system.
#CMD ["/sbin/my_init"]

CMD ["/app/cutelyst/docker/run-default.sh"]

COPY . /app/cutelyst


# ...put your own build instructions here...

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
