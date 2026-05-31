param(
    [string]$Message = "✅ Grok response finished."
)

$token = "8147243348:AAETIuvXaEeZywYND-IsoIPcrsiVd71VVlM"
$chatId = "7991613221"

try {
    Invoke-RestMethod -Uri "https://api.telegram.org/bot$token/sendMessage" -Method Post -Body @{
        chat_id = $chatId
        text = $Message
    } -ErrorAction Stop | Out-Null

    Write-Host "📨 Telegram ping sent: $Message" -ForegroundColor Green
} catch {
    Write-Host "❌ Failed to send Telegram notification: $_" -ForegroundColor Red
}
