
## Часть 3. SQL-задание
Дано: набор данных в таблице players со структурой полей:
`players(id INT, name VARCHAR, login_time DATETIME, device INT)`
Задание: сформулировать SQL-запросы для следующих случаев:
Получить 5 самых активных устройств – то есть пять значений поля device, с которых произошло наибольшее количество логинов пользователей (упорядочить по количеству логинов).


Получить среднее число логинов в день за последние 7 дней (в расчете от текущей даты).

## Решение

### Получить 5 значений поля device с наибольшим количеством логинов.

```
SELECT device, COUNT(*) AS login_count
FROM players
GROUP BY device
ORDER BY login_count DESC
LIMIT 5;
```

`COUNT(*)` - количество логинов
`GROUP BY device` - сгруппировать устройства
`ORDER BY ... DESC` - по убыванию
`LIMIT 5` - ограничение вывода 5 результатов

### Получить среднее число логинов в день за последние 7 дней.

```
SELECT 
    COUNT(*) / 7.0 AS average_logins_per_day
FROM players
WHERE 
    login_time >= CURRENT_DATE - INTERVAL '7 days'
    AND login_time < CURRENT_DATE + INTERVAL '1 day';
```

`CURRENT_DATE - INTERVAL '7 days'` - дата 7 дней назад
`login_time < ... + INTERVAL '1 day'` - включение текущего дня
`COUNT(*) / 7.0 - расчет среднего` (7.0 для дробного результата)