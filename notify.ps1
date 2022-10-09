Add-Type -AssemblyName System.Windows.Forms
$global:balloon = New-Object System.Windows.Forms.NotifyIcon
$path = (Get-Process -id $pid).Path
$balloon.Icon = [System.Drawing.Icon]::ExtractAssociatedIcon($path)
$balloon.BalloonTipIcon = [System.Windows.Forms.ToolTipIcon]::info
$balloon.BalloonTipText = 'I guess you need to see who it is!'
$balloon.BalloonTipTitle = "Someone is at your door..."
$balloon.Visible = $true
$balloon.ShowBalloonTip(9000)