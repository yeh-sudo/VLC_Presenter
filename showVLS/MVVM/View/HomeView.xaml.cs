using showVLS.Core;
using showVLS.MVVM.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace showVLS.MVVM.View {

    /// <summary>
    /// HomeView.xaml 的互動邏輯
    /// </summary>
    public partial class HomeView : UserControl {

        [DllImport(@"..\..\..\..\MyDll\x64\Debug\MyDll.dll", CharSet =CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Create(string x, int len);

        [DllImport(@"..\..\..\..\MyDll\x64\Debug\MyDll.dll")]
        public static extern int getURLLen(IntPtr input);

        [DllImport(@"..\..\..\..\MyDll\x64\Debug\MyDll.dll")]
        public static extern void openURL(IntPtr input);


        private string SearchBoxText;

        public HomeView() {
            InitializeComponent();
        }

        private void ShowButton_Click(object sender, RoutedEventArgs e) {
            SearchBoxText = SearchBox.Text;
            if (SearchBoxText == "") {
                return;
            }
            GlobalClass tmp = new GlobalClass();
            tmp.History = SearchBoxText;
            MainViewModel.HistoryList.Add(tmp);

            IntPtr input = Create(SearchBoxText, SearchBoxText.Length);
            openURL(input);
        }
    }
}
