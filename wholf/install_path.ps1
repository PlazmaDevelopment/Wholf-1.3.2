# Wholf PATH Installer

# Gerekli yönetici haklarını kontrol et
if (-not ([Security.Principal.WindowsPrincipal] [Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Host "Bu script yönetici haklarıyla çalıştırılmalıdır. Lütfen script'i yönetici olarak çalıştırın." -ForegroundColor Red
    exit
}

# Wholf klasörünün yolunu al
$wholfPath = "c:\Users\zubag\OneDrive\Masaüstü\wholf"

# Mevcut PATH'i al
$currentPath = [System.Environment]::GetEnvironmentVariable("Path", "Machine")

# Wholf klasörünü PATH'e ekle
if ($currentPath -notlike "*$wholfPath*") {
    $newPath = "$wholfPath;$currentPath"
    [System.Environment]::SetEnvironmentVariable("Path", $newPath, "Machine")
    
    # Sistem değişkenlerini güncelle
    $env:Path = [System.Environment]::GetEnvironmentVariable("Path", "Machine")
    
    Write-Host "Wholf başarıyla PATH'e eklendi!" -ForegroundColor Green
    Write-Host "Değişikliklerin etkili olması için bilgisayarınızı yeniden başlatmanız gerekecek." -ForegroundColor Yellow
} else {
    Write-Host "Wholf zaten PATH'de mevcut!" -ForegroundColor Green
}

# Kullanıcıya bilgi ver
Write-Host "" -ForegroundColor White
Write-Host "Wholf PATH Installer" -ForegroundColor Cyan
Write-Host "-------------------" -ForegroundColor Cyan
Write-Host "" -ForegroundColor White
Write-Host "Wholf klasörünün yolu: $wholfPath" -ForegroundColor White
Write-Host "" -ForegroundColor White
Write-Host "Not: Değişikliklerin etkili olması için bilgisayarınızı yeniden başlatmanız gerekecek." -ForegroundColor Yellow
Write-Host "" -ForegroundColor White
Write-Host "Bu pencere 10 saniye sonra kapanacaktır..." -ForegroundColor Yellow

# Pencereyi 10 saniye sonra kapat
Start-Sleep -Seconds 10
