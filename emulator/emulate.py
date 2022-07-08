#!/usr/bin/env python3

import time 
import math
import asyncio
import socket
import websockets

async def transmitSinusoid(websocket, path):
    delay = 0.05; amplitude = 1
    while True:
        for i in range(0, 91):
            time.sleep(delay)
            await websocket.send(str(amplitude * math.sin( i * (math.pi/180))))

        for i in range(0, 91):
            time.sleep(delay)
            await websocket.send(str(amplitude * math.sin( 90 - i * (math.pi/180))))

        for i in range(0, 91):
            time.sleep(delay)
            await websocket.send(str(amplitude * math.sin( -1 * i * (math.pi/180))))

        for i in range(0, 91):
            time.sleep(delay)
            await websocket.send(str(amplitude * math.sin( -1 * (90 - i) * (math.pi/180))))    

localIP = socket.gethostbyname(socket.gethostname())
print("Local IP: ".format(localIP))
asyncio.get_event_loop().run_until_complete(websockets.serve(transmitSinusoid, str(localIP), 8000))
asyncio.get_event_loop().run_forever()