# Create following simple VLANs network

In switch CLI type following commands:
```bash
   enable
```
```bash
   config terminal
```
---
```bash
   vlan 10
```
```bash
   name SALES
```
---
```bash
   vlan 20
```
```bash
   name IT
```
## Assign switch ports to the VLANs.

```bash
    Switch(config)#int fa0/1
    Switch(config-if)#switchport mode access
    Switch(config-if)#switchport access vlan 10
```
Do it for all the ports

---
---
# Inter-VLAN Routing
Do it in router

```bash
    config terminal
    int fa0/0
    no shutdown
```

```bash
    int fa0/0.10
    encapsulation dot1q 10
    ip add 192.168.1.1 255.255.255.0
```
