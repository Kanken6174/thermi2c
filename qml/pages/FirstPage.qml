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
                        polling_timer.stop();
                    }else{
                        mainPage.isInitialized = true;
                        mlx90640.fuzzyInit();
                        polling_timer.start();
                    }
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

            ComboBox{
                id: themes
                anchors.horizontalCenter: parent.horizontalCenter
                label: "Theme: "
                currentIndex: 2
                menu: ContextMenu
                {
                    MenuItem { text: "hotiron" }
                    MenuItem { text: "rainbow" }
                    MenuItem { text: "gray" }
                }
                onCurrentIndexChanged: {
                    thermalRenderer.setActiveAttributer(themes.currentIndex);
                }
              }
        }
    }
}
