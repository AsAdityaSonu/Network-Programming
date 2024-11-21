# Inter-VLAN Routing using Layer 3 switches

In switch CLI type following commands:
```bash
    D1(config)# vlan 10
    D1(config-vlan)# name LAN10
    D1(config-vlan)# vlan 20
    D1(config-vlan)# name LAN20
    D1(config-vlan)# exit
    D1(config)#
```

## Create the SVI VLAN interfaces
```bash
    interface vlan 10
```
```bash
    description Default Gateway SVI for 192.168.10.0/24
```
```bash
    ip add 192.168.10.1 255.255.255.0
```
```bash
    no shut
```
```bash
    exit
```

## Configure Access Ports
```bash
    interface GigabitEthernet1/0/6
```
```bash
    description access port to PC0
```
```bash
    switchport mode access
```
```bash
    switchport access vlan 20
```
```bash
    exit
```

## Enable IP Routing
```bash
    ip routing
```
