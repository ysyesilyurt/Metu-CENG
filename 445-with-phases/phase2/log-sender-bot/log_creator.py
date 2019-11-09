#!/usr/bin/env python3

import random

# ysyesilyurt

hosts = ["ali","veli","yavuz","halit","john","onur","alicia","mike","162.135.25.1","211.125.25.144","144.125.254.156","142.35.24.45","45.12.123.1","56.15.133.45","221.135.25.15","48.122.25.156"]

logs = ["NetworkManager Server returned error NXDOMAIN, mitigating potential DNS violation DVE-2018-0001, retrying transaction with reduced feature level UDP.",
"storehelpers.go cannot refresh: snap has no updates available: 'core', 'gnome-3-26-1604', 'gnome-calculator', 'gnome-characters', 'gnome-logs', 'gnome-system-monitor', 'gtk-common-themes','spotify'",
"systemd Starting Cleanup of Temporary Directories...",
"autorefresh.go all snaps are up-to-date",
"NetworkManager handshake failed; returned -1, SSL error code 1, net_error -107",
"Anacron Started Run anacron jobs.",
"Anacron Anacron 2.3 started on 2018-12-11",
"NetworkManager connectivity: (wlan0) timed out",
"NetworkManager NetworkManager state is now CONNECTED_SITE",
"NetworkManager Started Network NetworkManager Script Dispatcher Service.",
"Dispatcher req:1 'connectivity-change': new request (1 scripts)",
"Dispatcher req:1 'connectivity-change': start running ordered scripts...",
"RegDiiView <window.Window object at 0x7f1559367910 (terminatorlib+window+Window at 0x565507f5aa50)> is not in registered window list",
"NetworkManager NetworkManager state is now CONNECTED_GLOBAL",
"systemd Activating via systemd: service name='org.freedesktop.nm_dispatcher' unit='dbus-org.freedesktop.nm-dispatcher.service' requested by ':1.9' (uid=0 pid=1027 comm='/usr/sbin/NetworkNetworkManager --no-daemon ')",
"Dispatcher Starting Network NetworkManager Script Dispatcher Service...",
"freedesktop The default IPv4 route is: /org/freedesktop/NetworkNetworkManager/ActiveConnection/1",
"freedesktop Not a paid data plan: /org/freedesktop/NetworkNetworkManager/ActiveConnection/1",
"freedesktop Found usable connection: /org/freedesktop/NetworkNetworkManager/ActiveConnection/1",
"freedesktop Successfully activated service 'org.freedesktop.nm_dispatcher'",
"Dispatcher Started Network NetworkManager Script Dispatcher Service.",
"freedesktop Successfully activated service 'org.freedesktop.hostname1'",
"freedesktop WARNING: App 'spice-vdagent.desktop' exited with code 1",
"freedesktop Error looking up permission: GDBus.Error:org.freedesktop.DBus.Error.ServiceUnknown: The name org.freedesktop.impl.portal.PermissionStore was not provided by any .service files",
"nautilus reference to undefined property 'MetaWindowXwayland'",
"openConnection connect: No such file or directory",
"plymouthd Received SIGRTMIN+21 from PID 343 (plymouthd).",
"Bluetooth BNEP (Ethernet Emulation) ver 1.3",
"Bluetooth BNEP filters: protocol multicast",
"Bluetooth BNEP socket layer initialized",
"systemd  Unmounted /run/user/1000/gvfs.",
"gnomeNOTE Not using GLX TFP!",
"systemd Started Run anacron jobs.",
"anacron Anacron 2.3 started on 2018-11-24",
"chromium[2082:2095:1124/012020.580880:ERROR:socket_stream.cc(219)] Closing stream with result -2",
"kernel nvidia-modeset: WARNING: GPU:0: Correcting number of heads for current head configuration (0x00)",
"NetworkNetworkManager <info>  [1543020767.7895] dhcp4 (eth0):   address 10.0.0.2",
"kernel rfkill: input handler enabled",
"GtkFailed to load module 'gail'",
"GtkFailed to load module 'atk-bridge'",
"GtkFailed to load module 'canberra-gtk-module'",
"Gtk Could not load a pixbuf from icon theme.#012This may indicate that pixbuf loaders or the mime database could not be found.",
"systemd E: Sub-process nm-online returned an error code (1)",
"apt Started Daily apt download activities.",
"apt Starting Daily apt upgrade and clean activities...",
"apt Started Daily apt upgrade and clean activities.",
"kernel Startup finished in 4.687s (firmware) + 1.747s (loader) + 4.902s (kernel) + 44.590s (userspace) = 55.927s.",
"apt Starting Stop ureadahead data collection...",
"apt Started Stop ureadahead data collection.",
"systemd Activating via systemd: service name='org.freedesktop.fwupd' unit='fwupd.service' requested by ':1.107' (uid=1000 pid=2321 comm='/usr/bin/gnome-software --gapplication-service ')",
"uefi Starting Firmware update daemon...",
"uefi disabling plugin because: failed to startup dell: Firmware updating not supported",
"uefi disabling plugin because: failed to coldplug amt: ME refused connection",
"uefi disabling plugin because: failed to coldplug thunderbolt_power: missing kernel support for intel-wmi-thunderbolt",
"uefi disabling plugin because: failed to coldplug synapticsmst: MST firmware updating not supported by OEM",
"uefi using plugins: upower, csr, altos, steelseries, thunderbolt, ebitdo, dfu, colorhug, nitrokey, udev, unifying, uefi"]

def main():
    base = 0
    with open("generated.log", "w") as newLog:
        for i in range(50):
            hour = random.randrange(24)
            if hour / 10 == 0:
                hour = "0" + str(hour)
            minute = random.sample(range(61), 1)[0]
            if minute / 10 == 0:
                minute = "0" + str(minute)
            seconds = random.sample(range(61), 1)[0]
            if seconds / 10 == 0:
                seconds = "0" + str(seconds)
            code = "<" + str(random.randrange(192)) + ">"
            idnumber = random.sample(range(100), 1)[0]
            base += 1
            newLog.write(code + "1 " + "2018-11-12T"+ str(hour) + ":" + str(minute) +":"+ str(seconds) + ".003Z " + random.choice(hosts) + " " + random.choice(logs).replace(" "," - ID" + str(idnumber) + " - ",1) + '\n')

if __name__ == '__main__':
    main()
