# Basic CI/CD Pipeline

## 📌 Описание проекта

Проект реализует простой CI/CD pipeline для автоматической сборки, тестирования и развертывания утилит `cat` и `grep` (SimpleBashUtils) с использованием GitLab CI/CD.  
Pipeline автоматизирует процессы Continuous Integration и Continuous Delivery для небольшого Linux-проекта.

---

## ⚙️ Используемые технологии

- GitLab CI/CD, gitlab-runner  
- Bash  
- SSH / SCP  
- Ubuntu Server 22.04  
- Makefile  
- clang-format  

---

## 🧩 Этапы pipeline

1. **Build**
   - Сборка проекта через `make`.
   - Сохранение артефактов.

2. **Code Style Check**
   - Проверка форматирования кода с помощью `clang-format`.
   - При ошибке пайплайн завершается.

3. **Integration Tests**
   - Запуск интеграционных тестов.
   - Выполняется только при успешной сборке и кодстайле.

4. **Deploy (ручной этап)**
   - Копирование бинарных файлов на удалённую Linux-машину через `ssh` и `scp`.
   - Размещение в `/usr/local/bin`.

5. **Notifications (дополнительно)**
   - Отправка уведомлений о статусе pipeline в Telegram.

---

## 🎯 Цель проекта

Проект демонстрирует навыки настройки CI/CD pipeline, автоматизации сборки и тестирования, деплоя на удалённый сервер и написания Bash-скриптов для DevOps-задач.
