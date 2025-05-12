import imaplib, asyncio

from imap_tools.mailbox import MailBox

from textual.app import App, ComposeResult
from textual.widgets import Button, Header, Footer, Label, Input, Static, ListView, LoadingIndicator, ListItem
from textual.containers import Container 

GMAIL_IMAP_SERVER="imap.gmail.com"
GMAIL_IMAP_PORT=993

# Добавление главного окна
async def add_main_window(self, messages, reuse: bool):
    if not reuse:
        self.query_one("#mail_container").remove_class("hidden")
        items = []

        header_row = Container(
            Label("Отправитель", classes="header_sender"),
            Label("Тема", classes="header_subject"),
            Label("Дата", classes="header_date"),
            classes="header_row"
        )

        for msg in messages:
            row = Container(
                Label(msg["from"], classes="sender"),
                Label(msg["subject"], classes="subject"),
                Label(msg["date"], classes="date"),
                classes="email_row"
            )
            items.append(ListItem(row))

        # Добавим кнопку
        items.append(
            ListItem(
                Container(
                    Button("Показать ещё", id="show_more_button"),
                    classes="load_more_container"
                )
            )
        )

        list_view = ListView(*items, id="mail_list")
        container = self.query_one("#mail_container", Container)

        await container.mount(header_row)
        await container.mount(list_view)

    else:
        list_view = self.query_one("#mail_list", ListView)

        # Удаляем старую кнопку
        old_button = list_view.children[-1]
        await old_button.remove()

        # Добавляем письма
        for msg in messages:
            row = Container(
                Label(msg["from"], classes="sender"),
                Label(msg["subject"], classes="subject"),
                Label(msg["date"], classes="date"),
                classes="email_row"
            )
            await list_view.mount(ListItem(row))

        # Добавляем кнопку обратно
        await list_view.mount(
            ListItem(
                Container(
                    Button("Показать ещё", id="show_more_button"),
                    classes="load_more_container"
                )
            )
        )


class LoginBox(Static):
    def compose(self) -> ComposeResult:
        yield Label("Введите свой адрес почты (gmail) и пароль для imap приложений (получить его можно здесь: https://myaccount.google.com/apppasswords):", id="gmail_text")

        with Container(id="input_container"):
            yield Input(placeholder="example@gmail.com", id="email_input")
            yield Input(placeholder="password", password=True, id="password_input")

        yield Container(
                    Button("Login", id="login_button"),
                    id="button_container"
                )
        yield Static("", id="output", markup=False)


class EmailIMAP_Client(App):
    def on_mount(self) -> None:
        self.theme = "tokyo-night"
        self.query_one("#mail_container").add_class("hidden")
        self.loaded_letters = 0

    # BINDINGS = [("q", "exit", "Quit")]
    CSS_PATH = "index.tcss"

    def compose(self) -> ComposeResult:
        yield Header()
        yield Footer()
        yield Container(LoginBox(id="login_box"), id="login_container")
        yield Container(id="mail_container")


    async def on_button_pressed(self, event: Button.Pressed) -> None:
        if event.button.id == "login_button":
            email_input = self.query_one("#email_input", Input)
            email = email_input.value

            password_input = self.query_one("#password_input", Input)
            password = password_input.value

            output_widget = self.query_one("#output", Static)
    
            try:
                self.mb = MailBox(GMAIL_IMAP_SERVER, 993).login(email, password, "Inbox")
                output_widget.update(f"✅ Успешное подключение")
                self.query_one("#login_container", Container).remove()

                scroll = LoadingIndicator(id="loading")
                await self.mount(scroll)

                letters = []
                letters = await asyncio.to_thread(get_mail, self.mb, self.loaded_letters, 10)

                self.loaded_letters += len(letters)

                self.query_one("#loading", LoadingIndicator).remove()

                await add_main_window(self, letters, False)

            except imaplib.IMAP4.error as e:
                output_widget.update(f"❌ Ошибка авторизации: {e}")

            except Exception as e:
                output_widget.update(f"❌ Ошибка авторизации: {e}")


        elif event.button.id == "show_more_button":
            global loaded_letters

            letters = []
            letters = await asyncio.to_thread(get_mail, self.mb, self.loaded_letters, 10)

            self.loaded_letters += len(letters)
            await add_main_window(self, letters, True)



def get_mail(mb, start, count):
    letters = []
    skipped = 0
    collected = 0

    for msg in mb.fetch(reverse=True, headers_only=True):
        if skipped < start:
            skipped += 1
            continue
        if collected >= count:
            break

        letters.append({
            "subject": msg.subject,
            "from": msg.from_,
            "date": msg.date.strftime("%d %b %Y")
        })
        collected += 1

    return letters
if __name__ == "__main__":
    app = EmailIMAP_Client()
    app.run()
