#!/bin/bash
echo "Photobooth config script"

rm /var/crash/*
gvfs-mount -s gphoto2
