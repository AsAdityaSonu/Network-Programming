# Layer 3 Switch Topology
```bash
    interface f0/1
```
```bash
    no switchport
```
```bash
    ip address 10.10.10.2 255.255.255.0
```
```bash
    no shut
```
```bash
    exit
```

----
## Enable Routing
```bash
    ip routing
```

---
## Configure Routing
## Enable Routing
```bash
    router ospf 10
```
```bash
    network 192.168.10.0 0.0.0.255 area 0
```
```bash
    network 192.168.20.0 0.0.0.255 area 0
```
```bash
    network 10.10.10.0 0.0.0.3 area 0
```
---
## Verify Routing
```bash
    D1(config-router)# ^Z
    D1#
```
---
## Verify Connectivity
```bash
    ping 10.20.20.254
```
---