   M S B A M L   `   `   `  ���� >  :gui, Version=1.0.0.0, Culture=neutral, PublicKeyToken=nullclr-namespace:guigui      gui.MainWindow   W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     @d2http://schemas.microsoft.com/expression/blend/2008     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     #localclr-namespace:gui     _ [MaterialDesignThemes.Wpf, Version=4.2.1.2, Culture=neutral, PublicKeyToken=df2a72020bd7962aFmaterialDesign1http://materialdesigninxaml.net/winfx/xaml/themes    � Title$x  r                                                                                                            OurTor��$	��490��$	��800��.���  � ColumnDefinitions �� $	��270 ��� $��* �.+�� $��1�����	#FFE4E4E4�� $��0�����#ff8080.+��� $��55�� �� Orientation$ 
Horizontal=�
�������.+�� $��Center=�$��5q� �� $	��230 ��� $��35 �.+��� -    ��Name$ UserNameChats��$��
Your Chats��$��30(�$��Center=�$��Center=� �� TextAlignment$ Center=�$	��270��$��45��
��������� -   $��LogOut��$��Bottom=� *  &MaterialDesignFloatingActionMiniButton#��[  $��2��$��	225,0,0,3q���Z� ��Z� .���� $��Assets/logout.png��$��25��$��25��� $��Center=�$��45�� �� $	��230 ��� $��30 �.+��� -   $��
SearchText��$��20,0,0,3q� % !MaterialDesignFloatingHintTextBox#��[ )  #MaterialDesignThemes.Wpf.HintAssist   Hint$ SEARCH��$��13(�6  0MaterialDesignThemes.Wpf.BottomDashedLineAdorner   Brush
 �����   	Thickness$ 3q�$��40��
�������$
��Left=�$	��190���� -   $��
searchName��$��Bottom=�#��[  $��2��
 � Tag$ search��$��215,-1,2,-5q���Z� ��Z� .���� -   $��SearchBackground��$��Assets/search.png��$��20��$��20���� -   	 ��Name$	 	UsersList���� $��1�����#ffe6e6.+�� 
 � RowDefinitions
 �� $��55 ��� $	��340 ��� $��60 �.+��� -   $ UserName��$-��'Click on the user you want to chat with��$��29(�$��Center=�$��Center=�$ Center=�$	��522��$��55�����#fffafa�� -   $��MessagesList��$��1��$	��Top=�$��Stretch=�� $
��0 10q�$��2�� �� $��* ��� $��70 �.+��� ���#ffcccc$��Bottom=� �� CornerRadius$ 15 15 15 15��$��40��$��10,0,0,0q�._��� -	   $��Message��$��0��$��80�� �� TextWrapping$
 Wrap=�$��5q�$��15(�$ Type a message�� �� AcceptsReturn .  " �� VerticalScrollBarVisibility$
 Auto=��� -
   $��1��$��Bottom=�#��[  ��Z� ��Z� .���� $��Assets/SEND.png��$��40��$��40��