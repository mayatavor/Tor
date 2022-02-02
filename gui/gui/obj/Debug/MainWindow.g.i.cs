﻿#pragma checksum "..\..\MainWindow.xaml" "{8829d00f-11b8-4213-878b-770e8597ac16}" "AEE72EC90950FD084ACAEA9B67FC5782719FA088697026F10A6AEE6E754679D6"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using MaterialDesignThemes.Wpf;
using MaterialDesignThemes.Wpf.Converters;
using MaterialDesignThemes.Wpf.Transitions;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Shell;
using gui;


namespace gui {
    
    
    /// <summary>
    /// MainWindow
    /// </summary>
    public partial class MainWindow : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 42 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button LogOut;
        
        #line default
        #line hidden
        
        
        #line 59 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox SearchText;
        
        #line default
        #line hidden
        
        
        #line 75 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Button searchName;
        
        #line default
        #line hidden
        
        
        #line 81 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Image SearchBackground;
        
        #line default
        #line hidden
        
        
        #line 85 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListView UsersList;
        
        #line default
        #line hidden
        
        
        #line 100 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock UserName;
        
        #line default
        #line hidden
        
        
        #line 110 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ListView MessagesList;
        
        #line default
        #line hidden
        
        
        #line 126 "..\..\MainWindow.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBox Message;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/gui;component/mainwindow.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\MainWindow.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            this.LogOut = ((System.Windows.Controls.Button)(target));
            
            #line 43 "..\..\MainWindow.xaml"
            this.LogOut.Click += new System.Windows.RoutedEventHandler(this.LogOut_Click);
            
            #line default
            #line hidden
            return;
            case 2:
            this.SearchText = ((System.Windows.Controls.TextBox)(target));
            
            #line 63 "..\..\MainWindow.xaml"
            this.SearchText.KeyDown += new System.Windows.Input.KeyEventHandler(this.SearchInText_KeyDown);
            
            #line default
            #line hidden
            return;
            case 3:
            this.searchName = ((System.Windows.Controls.Button)(target));
            
            #line 78 "..\..\MainWindow.xaml"
            this.searchName.Click += new System.Windows.RoutedEventHandler(this.search_Click);
            
            #line default
            #line hidden
            return;
            case 4:
            this.SearchBackground = ((System.Windows.Controls.Image)(target));
            return;
            case 5:
            this.UsersList = ((System.Windows.Controls.ListView)(target));
            
            #line 85 "..\..\MainWindow.xaml"
            this.UsersList.PreviewMouseDoubleClick += new System.Windows.Input.MouseButtonEventHandler(this.UsersList_PreviewMouseDoubleClick);
            
            #line default
            #line hidden
            return;
            case 6:
            this.UserName = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 7:
            this.MessagesList = ((System.Windows.Controls.ListView)(target));
            return;
            case 8:
            this.Message = ((System.Windows.Controls.TextBox)(target));
            
            #line 129 "..\..\MainWindow.xaml"
            this.Message.KeyDown += new System.Windows.Input.KeyEventHandler(this.Message_KeyDown);
            
            #line default
            #line hidden
            return;
            case 9:
            
            #line 138 "..\..\MainWindow.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.SendMessage_Click);
            
            #line default
            #line hidden
            return;
            }
            this._contentLoaded = true;
        }
    }
}

