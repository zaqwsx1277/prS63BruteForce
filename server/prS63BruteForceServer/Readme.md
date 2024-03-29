# Описание алгоритма работы сервера для распределённой системы подбора пароля по раскодированию файлов защищённых по схеме S63

## Прием/передача данных в распределённой системе:
* После нахождения сервера, клиент посылает запрос на подключение cmdConnectionRequest.
* Сервер либо подтверждает подключение cmdConnectionConfirm и в этом же кадре передает клиенту размер обрабатываемого блока, либо отказывается от подключения (условия такого отказа пока неопределены).
* При успешном подключении сервер выделяет каждому клиенту свой поток threadClient в котором будет вестись обмен информацией с клиентом.
* У сервера существует контейнер std::set в котором хранится вся информация о потоке, ключом у которого является id-потока. Т.к.для обеспечения потокобезопасности данного контейнера при работе с данными блокируется любой доступ нему, то предприняты специальные меры по минимизации времени данной блокировки.
* Получив/передав данные threadClient записывает эти данные в контейнер std::quere и запускает менеджер обработки данных выполняемый в отдельном потоке threadDataManager. В данный контейнер так же записываются сообщения об ошибках.
* Если запущен хоть один threadDataManager, то он выполняет обработку всех команд записаных в контейнер и только обработав всю очередь завершает свою работу, при этом другие threadDataManager для обработки данных не запускаются
* При завершении работы сервера, выполняется ожидание завершения всех потоков и обработки всех команд. 

Все возможный состояния сервера приведены на файле "Граф переходов состояний сервера.pdf"

