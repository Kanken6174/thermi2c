import Sailfish.Silica 1.0
import harbour.i2ctool.I2cif 1.0
import melexis.driver 1.0
import QtQuick 2.0

Page {
    id: mainPage
    property bool isInitialized: false

    MLX90640 {
        id: thermal
    }

    SilicaFlickable {
        anchors.fill: parent

        Column {
            anchors.horizontalCenter: parent.horizontalCenter

            Button {
                id: startButton
                text: mainPage.isInitialized ? "Stop" : "Start"
                onClicked: {
                    if(mainPage.isInitialized){
                        mainPage.isInitialized = false;
                        pollingTimer.stop();
                    }else{
                        thermal.fuzzyInit();
                        //mainPage.isInitialized = true;
                        //pollingTimer.start();
                    }
                }
            }

            Grid {
                id: grid
                columns: 32

                Repeater {
                    model: 768
                    delegate: Rectangle {
                        width: 15
                        height: 15
                        color: (index % 64 < 32) ? (index % 2 === 0 ? "red" : "blue") : (index % 2 === 0 ? "blue" : "red")
                    }
                }
            }
        }
    }

    Timer {
        id: pollingTimer
        interval: 1000
        repeat: true
        running: false
        onTriggered: {
            thermal.getData();
        }
    }
}
