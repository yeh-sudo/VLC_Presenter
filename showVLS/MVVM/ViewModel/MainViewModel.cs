using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using showVLS.Core;

namespace showVLS.MVVM.ViewModel {
    internal class MainViewModel : ObservableObject {

        public RelayCommand HomeViewCommand { get; set; }

        public RelayCommand HistroyViewCommand { get; set; }

        public HomeViewModel HomeVM { get; set; }

        public HistoryViewModel HistoryVM { get; set; }

        private object _currentView;

        public object CurrentView {
            get { return _currentView; }
            set { 
                _currentView = value; 
                OnPropertyChanged(nameof(CurrentView));
            }
        }

        public MainViewModel() {
            HomeVM = new HomeViewModel();
            HistoryVM = new HistoryViewModel();
            CurrentView = HomeVM;

            HomeViewCommand = new RelayCommand(o => {
                CurrentView = HomeVM;
            });

            HistroyViewCommand = new RelayCommand(o => {
                CurrentView = HistoryVM;
            });
        }
    }
}
