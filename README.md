# README
Simple solution for getting weather info from BME280 sensor, connected to Arduino Nano RP2040 Connect, pushing it to a MQTT broker (RabbitMQ MQTT) and getting that data to InfluxDB via Telegraf subscribing to MQTT.
## Overview
![Overview Diagram](diagram.png)

## Setup

```
docker run -d --hostname rabbithost --name rabbit-name rabbitmq:3
docker run -d --hostname rabbit-chg --name rabbit-mgmt -p 8080:15672 -p 1883:1883  rabbit-management-chg:latest
docker run -d --name=influxdb -p 8086:8086 -v  /tmp/testdata/influx:/root/.influxdb2 influxdb:2.0
docker run -d -v $PWD/telegraf.conf:/etc/telegraf/telegraf.conf:ro telegraf
```

## To Do
- [ ] Move docker configuration to docker compose
- [ ] Add Arduino wiring sketch
- [ ] Connect Graphana to InfluxDB
- [ ] Refactor weather_sensor code

You need a InfluxDB API token, here is a [description how to get one](https://docs.influxdata.com/influxdb/cloud/security/tokens/create-token/).
