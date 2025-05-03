const net = require("net");
const fs = require("fs");
const os = require("os");

// Логирование
const LOG_FILE = "logs.log";

function log(message, level = "INFO") {
    const timestamp = new Date().toISOString().replace("T", " ").split(".")[0];
    const logMessage = `${timestamp} - ${level} - ${message}`;
    console.log(logMessage);
    try {
        fs.appendFileSync(LOG_FILE, logMessage + os.EOL, { encoding: "utf-8" });
    } catch (e) {
        console.error("Ошибка при записи в лог-файл:", e.message);
    }
}

// Чтение конфигурации
const CONFIG_FILE = "config.json";

if (!fs.existsSync(CONFIG_FILE)) {
    log("Ошибка: конфигурационный файл не найден. Выход.", "ERROR");
    process.exit(1);
}

let config;
try {
    const rawData = fs.readFileSync(CONFIG_FILE);
    config = JSON.parse(rawData);
} catch (e) {
    log(`Ошибка: не удалось прочитать конфигурационный файл: ${e.message}. Выход.`, "ERROR");
    process.exit(1);
}

// Проверка ключей и преобразование типов
let PORT, HOST, HANDLER_DELAY, WORKING_TIME;
try {
    PORT = parseInt(config.port);
    HOST = config.ip_addres;
    HANDLER_DELAY = parseInt(config.handler_delay);
    WORKING_TIME = parseInt(config.working_time) * 1000;

    if (!PORT || !HOST || !HANDLER_DELAY || !WORKING_TIME) {
        throw new Error("Один или несколько параметров отсутствуют или некорректны.");
    }
} catch (e) {
    log(`Ошибка: неверный формат конфигурации: ${e.message}. Выход.`, "ERROR");
    process.exit(1);
}

// Создание сервера
const server = net.createServer((socket) => {
    const clientAddress = `${socket.remoteAddress}:${socket.remotePort}`;
    log(`Установлено соединение с клиентом: ${clientAddress}`);

    const startTime = Date.now();
    socket.setTimeout(1000);

    socket.on("data", (data) => {
        try {
            const now = Date.now();
            if (now - startTime >= WORKING_TIME) return;

            const message = data.toString().trim();
            log(`Получено сообщение от клиента ${clientAddress}: '${message}'`);

            setTimeout(() => {
                try {
                    const response = `${message.split("").reverse().join("")}. Сервер написан Егоровым А.В. М3О-125БВ-24`;
                    socket.write(response);
                    log(`Сообщение отправлено клиенту ${clientAddress}: '${response}'`);
                } catch (sendError) {
                    log(`Ошибка при отправке данных клиенту ${clientAddress}: ${sendError.message}`, "ERROR");
                }
            }, HANDLER_DELAY * 1000);
        } catch (dataError) {
            log(`Ошибка при обработке данных от клиента ${clientAddress}: ${dataError.message}`, "ERROR");
        }
    });

    socket.on("timeout", () => {
        if (Date.now() - startTime >= WORKING_TIME) {
            try {
                socket.write("\nКлиент отключен от сервера.");
                socket.end();
                log(`Клиент отключен от сервера: ${clientAddress}`);
            } catch (timeoutError) {
                log(`Ошибка при завершении соединения с клиентом ${clientAddress}: ${timeoutError.message}`, "ERROR");
            }
        }
    });

    socket.on("end", () => {
        log(`Клиент отключился: ${clientAddress}`);
    });

    socket.on("error", (err) => {
        log(`Ошибка соединения с клиентом ${clientAddress}: ${err.message}`, "ERROR");
    });

});

server.on("error", (err) => {
    log(`Ошибка сервера: ${err.message}`, "ERROR");
    process.exit(1);
});

try {
    server.listen(PORT, HOST, () => {
        log("Сервер запущен. Ожидание сообщений...");
    });
} catch (e) {
    log(`Ошибка при запуске сервера: ${e.message}`, "ERROR");
    process.exit(1);
}

