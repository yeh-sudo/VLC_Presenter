using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Configuration;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace showVLS.Core {
    public class GlobalClass : INotifyPropertyChanged{
        public event PropertyChangedEventHandler PropertyChanged;
        private string _history;
        public string History { 
            get { return _history; }
            set { 
                _history = value;
                if (PropertyChanged != null) {
                    PropertyChanged(this, new PropertyChangedEventArgs(nameof(History)));
                }
            }
        }
    }
}
