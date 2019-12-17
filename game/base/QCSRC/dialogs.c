float quest;
float choice;
float d_cursor_x;
float d_cursor_y;
float number_choices;
float nextchoice_y;
float choice_complite[5];
float question;
string answer1;
string answer2;
string answer3;
string answer4;
string answer5;
string answer6;
string question1;
string question2;
float currentlengh;
float lengh;
.float talkperson;
float SIDOR = 1;
/*
сделать проверку на наличие определенного предмета в инвентаре
для диалогов
*/

void()dialog_down=
{
	if(choice >= number_choices)
	{
		d_cursor_x = 82;
		d_cursor_y = 160;
		choice = 1;
		ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
		return;
	}
	choice += 1;
	d_cursor_y += 16;
	ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
}
void()dialog_up=
{
	if(choice >= number_choices)
	{
		d_cursor_x = 82;
		d_cursor_y = 160;	
		choice = 1;
		ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
		return;
	}
	if(choice == 1)
	{
		d_cursor_x = 82;
		d_cursor_y = 176;	
		choice = 2;
		ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
		return;
	}
	choice -= 1;
	d_cursor_y -= 16;
	ShowString("cursor",">",d_cursor_x,d_cursor_y,8);
}
void()clear_text=
{
	for(float i = 0; i <= 19; i++)
	{
		ShowString(s[i],"",0,0,8);
	}
}
void()dialog_choice=
{
	if(self.talkperson == 1)
		dialog_choice_sidor();
	if(self.talkperson == 2)
		dialog_choice_tolyan();
}