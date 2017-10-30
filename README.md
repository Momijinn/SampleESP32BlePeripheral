SampleESP32BlePeripheral
====
ESP32をPeripheralとしてBle通信をするサンプルプログラム

## Description
ESP32をPeripheralとしてBle通信を行い、1秒毎ごとに6コのデータを送信しているサンプルプログラム


## Requirement
* ESP32

## Usage
* Arduino上でESP32のプログラムをかけるようにする

    http://www.autumn-color.com/archives/673

* Timerを使ってNotifyの更新を行っています

    * BLEDevice::init();

        デバイス名の設定


    * BLEServer *pServer = BLEDevice::createServer();

        Serverの設定

    * pCharacteristic = pService->createCharacteristic();

    * pCharacteristic->addDescriptor(new BLE2902());

        サービスの定義(Characteristic)

    * pService->start();

        サーバーのスタート

    * pServer->getAdvertising()->start();

        アドバタイジングのスタート

## Install
* myESP32Peripheral.inoをESP32へ書き込む

## Licence
This software is released under the MIT License, see LICENSE.

## Author
[Twitter](https://twitter.com/momijinn_aka)

[Blog](http://www.autumn-color.com/)