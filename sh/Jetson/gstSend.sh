gst-launch-1.0 v4l2src device=/dev/video0 ! videoflip method=0 ! video/x-raw,format=BGR,width=1280,height=720,framerate=30/1 ! videoconvert ! omxh264enc insert-sps-pps=true ! rtph264pay mtu=1400 config-interval=1 pt=96 ! udpsink host=10.0.0.1 port=56791