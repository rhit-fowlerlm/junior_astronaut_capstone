from serial.tools.list_ports import comports
import os

firmware_file = "~/junior_astronaut_capstone/Arduino/.pio/build/megaatmega2560/firmware.hex"

def run():
    ports = comports(include_links=True)
    device = None
    for p in ports:
        if p.description is not None and "arduino" in p.description.lower():
            device = p.device
        if p.manufacturer is not None and "arduino" in p.manufacturer.lower():
            device = p.device
        if p.product is not None and "arduino" in p.product.lower():
            device = p.device
        if p.name is not None and "arduino" in p.name.lower():
            device = p.device
        if p.hwid is not None and "arduino" in p.hwid.lower():
            device = p.device
        if p.interface is not None and "arduino" in p.interface.lower():
            device = p.device

    if device is None:
        print("No device found")
        return
    
    cmd = f"avrdude -c arduino -P {device} -c stk500v2 -b 115200 -p atmega2560 -D -U flash:w:{firmware_file}:i"
    os.system(cmd)


run()