
**Модуль 1.  Знайомство з Wi-Fi модулем ESP8266 та Arduino IDE. Керування портами вводу-виводу**
---------------------------


Зміст
=================

   * [gh-md-toc](#gh-md-toc)
   * [Installation](#installation)
   * [Usage](#usage)
      * [STDIN](#stdin)
      * [Local files](#local-files)
      * [Remote files](#remote-files)
      * [Multiple files](#multiple-files)
      * [Combo](#combo)
   * [Tests](#tests)
   * [Dependency](#dependency)


Colons can be used to align columns.

| Tables        | Are           | Cool  |
| ------------- |:-------------:| -----:|
| col 3 is      | right-aligned | $1600 |
| col 2 is      | centered      |   $12 |
| zebra stripes | are neat      |    $1 |

There must be at least 3 dashes separating each header cell.
The outer pipes (|) are optional, and you don't need to make the 
raw Markdown line up prettily. You can also use inline Markdown.

Markdown | Less | Pretty
--- | --- | ---
*Still* | `renders` | **nicely**
1 | 2 | 3

Three or more...

---

Hyphens

***

Asterisks

___

Underscores



> 1. вступ по мікроконтролерам (актуальність і тд)
> - [Встановлення програмного забеспечення та ознайомлення з теоритисними відомостями](#Встановлення-програмного-забезпечення-для-роботи-з-контролером ).
> - Написання першої програми "Блінк" та програмування мікроконтролера.
> 4. Приклад з роботою серіал  порту
> 5. Приклад з роботою GPIO  та збирання схеми з світлодіодом
> - Робота з ШІМ
> - Аналоговий вихід що підключається до підлаштовуючих резисторів
> - Приклад керування світлодіодами з серіал порту

Встановлення програмного забезпечення для роботи з контролером
-------

1.	Завантажте та встановіть Arduino IDE з офіційного веб-сайту.
1.	Запустіть Arduino IDE та відкрийте вікно налаштувань.
1.	Додайте наступну URL стрічку в поле «Менеджер додаткових плат». http://arduino.esp8266.com/stable/package_esp8266com_index
 ![Налаштування](ESP8266/image1.png)
1.	Відкрийте Менеджер плат з меню Інструменти > Плата: тазнайдітьплатформуesp8266.
1.	Виберіть найактуальнішу версію успадному списку (на момент написання цієї документації це є версія 2.3.0).
1.	Натисніть кнопку "Встановити".
1.	Незабудьте обрати вашу конфігурацію плати ESP8266, задопомогоюменю Інструменти > Плата: після встановлення.

P.S. Також, за бажанням, ви можете використати тестовий пакунок менеджера плат: http://arduino.esp8266.com/staging/package_esp8266com_index.json. 
Він може містити деякі нові функції, але в той же час деякі речі можуть неправильно працювати.

Перелік посилань:	
http://esp8266.github.io/Arduino/versions/2.3.0/

```
git status
git add
git commit
```

- [x] Finish my changes
- [x] Push my commits to GitHub
- [ ] Open a pull request

~~~python
import time
# Quick, count to ten!
for i in range(10):
    # (but not *too* quick)
    time.sleep(0.5)
    print i
~~~