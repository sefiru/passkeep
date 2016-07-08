package com.sefianti.comarduino;

import jssc.*;

import java.awt.*;

public class Main {
    private static SerialPort serialPort;
    private static Keyboard keyboard;

    public static void main(String[] args) throws SerialPortException, AWTException {
        keyboard = new Keyboard();
        serialPort = new SerialPort("COM5");
        serialPort.openPort();
        serialPort.setParams(SerialPort.BAUDRATE_9600, SerialPort.DATABITS_8, SerialPort.STOPBITS_1,
                             SerialPort.PARITY_NONE);
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN |
                                              SerialPort.FLOWCONTROL_RTSCTS_OUT);
        serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
    }

    private static class PortReader implements SerialPortEventListener {

        public void serialEvent(SerialPortEvent event) {
            if ( event.isRXCHAR() && event.getEventValue() > 0 ) {
                try {
                    String data = serialPort.readString(event.getEventValue());
                    keyboard.type(data.trim());
                }
                catch (SerialPortException ex) {
                    System.out.println(ex);
                }
            }
        }
    }
}