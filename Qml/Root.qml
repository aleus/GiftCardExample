/// @author M. A. Serebrennikov
import QtQuick 2.12
import QtQuick.Window 2.12
import Sp 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    color: Colors.background

    ListView {
        delegate: Provider {}
        model: ProvidersModel { }
        anchors.fill: parent
        topMargin: Consts.marginMiddle
    }
}
