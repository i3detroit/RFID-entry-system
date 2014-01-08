#!/usr/bin/env python

class OAC_Host:

    def __init__(self,port='/dev/ttyO4',baud=115200):
        '''Initialise OAC_Host instance
        
        Args:
            port -- serial port to use (default /dev/ttyO4)
            baud -- baudrate to use (default 115200)
            
        '''
        self._port = serial.Serial(port=port,baudrate=baud)

    def write(self,msg):
        '''Write message.'''
        self._port.write(msg + '\r\n')

    def read(self,byte=1):
        '''Read bytes.'''
        return self._port.read(byte)

    def relay(self,channel,state):
        '''Set the relay at channel to state'''
        if state:
            self.write('ON;%1d'%channel)
        else:
            self.write('OFF;%1d'%channel)

    def toggle(self,channel,duration):
        #TODO select() with pySerial for asynch messages?
