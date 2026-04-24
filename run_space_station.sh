if [ -z $XDG_SESSION_DESKTOP ]
then
echo "not in the desktop"
else
source /home/space-station/Documents/test/env/bin/activate
python /home/space-station/Documents/test/main.py
fi
