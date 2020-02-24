# /bin/bash

mkdir Linux
mkdir Windows
cd Linux
git clone https://github.com/TH3xACE/SUDO_KILLER.git
wget https://raw.githubusercontent.com/rebootuser/LinEnum/master/LinEnum.sh
wget https://raw.githubusercontent.com/diego-treitos/linux-smart-enumeration/master/lse.sh
https://raw.githubusercontent.com/sleventyeleven/linuxprivchecker/master/linuxprivchecker.py

cd ..
cd Windows
git clone https://github.com/AlessandroZ/BeRoot.git
https://raw.githubusercontent.com/AonCyberLabs/Windows-Exploit-Suggester/master/windows-exploit-suggester.py
git clone https://github.com/pentestmonkey/windows-privesc-check.git
cd ps1
git clone https://github.com/PowerShellMafia/PowerSploit.git
wget -N https://raw.githubusercontent.com/411Hall/JAWS/master/jaws-enum.ps1
wget -N https://raw.githubusercontent.com/M4ximuss/Powerless/master/Powerless.bat
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Exfiltration/Invoke-Mimikatz.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Exfiltration/Get-GPPPassword.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Exfiltration/Invoke-NinjaCopy.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Exfiltration/VolumeShadowCopyTools.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Escalation/Invoke-PsUACme.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Privesc/PowerUp.ps1
wget -N https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/situational_awareness/network/powerview.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/CodeExecution/Invoke-Shellcode.ps1
wget -N https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/CodeExecution/Invoke-WmiCommand.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Utility/Add-Exfiltration.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Utility/Do-Exfiltration.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Backdoors/Gupt-Backdoor.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Backdoors/DNS_TXT_Pwnage.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Utility/Out-DnsTxt.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Gather/Get-Information.ps1
wget -N https://raw.githubusercontent.com/samratashok/nishang/master/Gather/Get-WLAN-Keys.ps1
wget -N https://raw.githubusercontent.com/besimorhino/powercat/master/powercat.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Inveigh/master/Inveigh-Relay.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Inveigh/master/Inveigh.ps1
wget -N https://raw.githubusercontent.com/jaredhaight/PowerPunch/master/Documentation/Get-Attack.ps1
wget -N https://raw.githubusercontent.com/jaredhaight/PowerPunch/master/Code_Execution/Invoke-MetasploitPayload/Invoke-MetasploitPayload.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Tater/master/Tater.ps1
wget -N https://raw.githubusercontent.com/FuzzySecurity/PowerShell-Suite/master/Invoke-MS16-032.ps1
wget -N https://raw.githubusercontent.com/putterpanda/mimikittenz/master/Invoke-mimikittenz.ps1
wget -N https://raw.githubusercontent.com/jaredhaight/PowerPunch/master/Persistence/New-ScheduledTaskZ.ps1
wget -N https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/credentials/Invoke-Kerberoast.ps1
wget -N https://raw.githubusercontent.com/lukebaggett/dnscat2-powershell/master/dnscat2.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Invoke-TheHash/master/Invoke-SMBClient.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Invoke-TheHash/master/Invoke-SMBExec.ps1
wget -N https://raw.githubusercontent.com/Kevin-Robertson/Invoke-TheHash/master/Invoke-WMIExec.ps1
wget -N https://raw.githubusercontent.com/hlldz/Invoke-Phant0m/master/Invoke-Phant0m.ps1
wget -N https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/collection/vaults/KeePassConfig.ps1
wget -N https://raw.githubusercontent.com/jaredhaight/PowerPunch/master/Persistence/New-WMIPersistence.ps1
wget -N https://raw.githubusercontent.com/enigma0x3/Misc-PowerShell-Stuff/master/Invoke-EventVwrBypass.ps1
