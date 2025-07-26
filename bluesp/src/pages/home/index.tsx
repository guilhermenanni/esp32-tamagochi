import React, { useEffect, useState } from "react";
import {Buffer} from "buffer";
import { Button, Text, View, PermissionsAndroid, Platform } from 'react-native';
import { BleManager, Device } from 'react-native-ble-plx';

import { style } from "./styles";

const manager = new BleManager();

export default function Home() {
    const [log, setLog] = useState('');
    const [device, setDevice] = useState<Device | null>(null);

    async function requestPermissions() {
        if (Platform.OS === 'android') {
            await PermissionsAndroid.requestMultiple([
                PermissionsAndroid.PERMISSIONS.BLUETOOTH_SCAN,
                PermissionsAndroid.PERMISSIONS.BLUETOOTH_CONNECT,
                PermissionsAndroid.PERMISSIONS.ACCESS_FINE_LOCATION
            ])
        }

    }

    useEffect(() => {
        requestPermissions();
    }, []);

    const scanAndConnect = () => {
        setLog("escaneando dispositivos..");
        manager.startDeviceScan(null, null, (error, scannedDevice) => {
            if (error) {
                setLog("Erro: " + error.message);
                return;
            }

            if (scannedDevice && scannedDevice.name === 'bluesp') {
                setLog("Dispositivo encontrado: " + scannedDevice.name);
                manager.stopDeviceScan();
                scannedDevice.connect()
                    .then((device) => {
                        setDevice(device);
                        setLog("Conectado");
                        return device.discoverAllServicesAndCharacteristics();
                    });
            }

        });
    };

    const sendBlink = async () => {
        if (!device) return;
        await device.writeCharacteristicWithResponseForService(
            "12345678-1234-1234-1234-1234567890ab", // Service UUID
            "abcd1234-ab12-cd34-ef56-abcdef123456", // Characteristic UUID
            Buffer.from("blink").toString('base64') // Dado enviado
        );
        setLog("comando enviado: blink");
    }


    return (


        <View style={style.container}>

            <View style={style.tittle}>
                <Text style={style.tittleText}>Enviar comandos</Text>
            </View>

            <View style={style.buttons}>
                <Button title="blink" onPress={sendBlink} />
            </View>

            <View style={style.bottomStatusBar}>
                <Text style={style.bottomText}>okkkkkkkkkkk</Text>
            </View>

        </View>

    );
}