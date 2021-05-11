import React from 'react';
import { Navbar } from './components/navbar/Navbar';
import './assets/scss/argon-dashboard.scss';
import { DashboardCard } from './components/card/DashboardCard';
import { Loader } from './components/loading/Loader';
import { baseUrl, allUrl, relayTurnOnUrl, relayTurnOffUrl } from './constants/Route';


export class App extends React.Component {

  constructor(props) {
    var today = new Date(),
      time = today.getHours() + ':' + today.getMinutes() + ':' + today.getSeconds();
    super(props)

    this.state = {
      isLoading: true,
      hasfailed: false,
      dataUrl: allUrl,
      data: {},
      currentTime: time
    };
  }

  componentDidMount() {
    this.getSensorData(baseUrl + allUrl);
  }

  refresh = () => {
    this.getSensorData(baseUrl + allUrl);
  }

  getSensorData = (url) => {
    this.setLoading(true,
      () => fetch(url)
        .then(response => response.json())
        .then(data => this.setState(() => {
          return {
            isLoading: false,
            hasfailed: false,
            data
          }
        }))
        .catch(error => {
          console.log("web call failed " + error);
          this.requestHasFailed();
        })
    );
  }

  sensorAction = (url) => {
    this.setLoading(true,
      () => fetch(url)
        .then(() => this.getSensorData(baseUrl + allUrl))
        .catch(error => {
          console.log("web call failed " + error);
          this.requestHasFailed();
        })
      , () => this.getSensorData(baseUrl + allUrl));
  }

  requestHasFailed = () => {
    this.setState(() => {
      return {
        isLoading: false,
        hasfailed: true
      }
    })
  }

  setLoading = (isLoading, callback) => {
    this.setState(() => {
      return {
        isLoading,
        hasfailed: false
      }
    }, () => {
      if (callback) {
        callback();
      }
    })
  }

  render() {

    const { isRelayOn, temp, moisture, humidity } = this.state.data;
    let relayValue = isRelayOn;
    let moistureValue = moisture;
    let tempValue = temp;
    let humidityValue = humidity;
    const mysyle = {
      backgroundImage: "url(" + "https://mohammed-ismail.co.za/offerZen/img/background.jpg" + ")"
    }

    if (this.state.isLoading) {
      relayValue = 'Loading...';
      tempValue = 'Loading...';
      humidityValue = 'Loading...';
      moistureValue = 'Loading...';
    } else if (this.state.hasfailed) {
      relayValue = 'Unknown';
      tempValue = 'Unknown';
      humidityValue = 'Unknown';
      moistureValue = 'Unknown';
    } else {
      relayValue = isRelayOn ? 'On' : 'false';
    }
    let currentsoilString = 'Value above shows the current soil Moisture as at: ' + this.state.currentTime;
    return (
      <>

        <div className="main-content">
          <div style={mysyle} className="header c full-height pb-8 pt-5 pt-md-8">
            <div className="container-fluid">
              <div className="header-body">
                <div className="row">
                  <div className="col-xl-12 col-lg-6">
                    <DashboardCard
                      title="Soil Moisture"
                      value={moistureValue}
                      unit=" %"
                      icon="fa fa-leaf"
                      iconColour="bg-green"
                      description={currentsoilString}
                    />
                  </div>

                </div>
              </div>
            </div>
          </div>
        </div>
        {
          this.state.isLoading && <Loader />
        }
      </>
    );
  }
};
