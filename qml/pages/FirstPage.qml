import Sailfish.Silica 1.0
import harbour.i2ctool.I2cif 1.0
import melexis.driver 1.0
import QtQuick 2.0

Page {
    id: mainPage
    property bool isInitialized: false

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
                        mainPage.isInitialized = true;
                        mlx90640.fuzzyInit();
                        pollingTimer.start();
                    }
                }

                TextArea{
                    text:  mlx90640.getImageVectAt(100)
                }
            }

            Grid {
                id: grid
                columns: 32
                Repeater {
                    id: repeater
                    model: 768
                    Rectangle {
                        id: rectangle
                        width: 15
                        height: 15
                        property int rowIndex: Math.floor(index / 32)
                        property int columnIndex: index % 32
                        property int invertedIndex: (23 - rowIndex) * 32 + columnIndex
                        property real value: mlx90640.getImageVectAt(invertedIndex)
                        property real minValue: -3000000.000000
                        property real maxValue: -1000000.000000
                        property real hue: 0.67 - ((value - minValue) / (maxValue - minValue) * 0.67)
                        property color sensorColor: Qt.hsva(hue, 1, 1, 1)
                        color: sensorColor
                    }
                }

                Connections {
                    target: mlx90640
                    onDataReady: {
                        // force the repeater to update its items
                        repeater.model = [];
                        repeater.model = 768;
                    }
                }
            }

            Timer {
                id: pollingTimer
                interval: 70
                repeat: true
                onTriggered: {
                    mlx90640.getData();
                }
            }
        }
    }
}
