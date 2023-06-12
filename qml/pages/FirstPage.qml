import Sailfish.Silica 1.0
import harbour.i2ctool.I2cif 1.0
import melexis.driver 1.0
import QtQuick 2.0

Page {
    id: mainPage
    property bool isInitialized: false

    SilicaListView  {
        anchors.fill: parent
        PullDownMenu {
            id: menu

            Repeater {
                id: repk
                model: thermalRenderer.attributerNames
                delegate: MenuItem {
                    text: modelData
                    onClicked: {
                        console.log("Clicked " + text)
                        thermalRenderer.setActiveAttributer(index)
                    }
                }
            }
        }
        Column {
            id: column
            width: parent.width
            spacing: Theme.paddingLarge

            PageHeader
            {
                title: "ThermI2C"
            }

        Connections {
            target: thermalRenderer
            onAttributersChanged: {
                repk.model = []
                repk.model = thermalRenderer.attributerNames
                }
            }

        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            Button {
                id: startButton
                text: mainPage.isInitialized ? "Stop" : "Start"
                onClicked: {
                    if(mainPage.isInitialized){
                        mainPage.isInitialized = false;
                        polling_timer.stop();
                    }else{
                        mainPage.isInitialized = true;
                        mlx90640.fuzzyInit();
                        polling_timer.start();
                    }
                }

            }
        }

        Row
        {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter:  parent.verticalCenter
            anchors.verticalCenterOffset: -100
            Grid {
                id: grid
                columns: 32
                y: parent.height + height
                x: (parent.width + width) / 2
                Repeater {
                    id: repeater
                    model: 768
                    Rectangle {
                        id: rectangle
                        width: 15
                        height: 15
                        color: thermalRenderer.getDataForIndex(index)
                    }
                }
                Connections {
                    target: thermalRenderer
                    onDataChanged: {
                        for (var i = 0; i < repeater.count; i++) {
                            var item = repeater.itemAt(i);
                            if (item) {
                                item.color = thermalRenderer.getDataForIndex(i);
                            }
                        }
                    }
                }
            }
        }
        }
    }
}
