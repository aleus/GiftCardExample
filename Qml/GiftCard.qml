import QtQuick 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls.Material 2.12
import QtQuick.Controls.Material.impl 2.12

Item {
    id: _giftCard

    property alias bottomColor: bottom.color

    width: Consts.giftCardWidth
    height: Consts.giftCardHeight

    Rectangle {
        id: shadowItem

        anchors.fill: parent
        radius: 0.5*height
        color: "transparent"
        transform: Translate { y: Consts.shadowShiftSmall }
        layer.enabled: true
        layer.effect: ElevationEffect {
            elevation: 1
        }
    }

    Rectangle {
        id: background

        color: Colors.cardBackground
        radius: Consts.radius
        clip: true
        anchors.fill: parent
    }

    Item {
        id: corner

        anchors.fill: background
        visible: false

        Rectangle {
            color: Colors.corner1
            width: parent.width
            height: 23*dp
            rotation: -26
            anchors.horizontalCenter: parent.left
        }

        Rectangle {
            color: Colors.corner0
            width: parent.width
            height: 10*dp
            rotation: -18
            anchors.horizontalCenter: parent.left
        }
    }

    OpacityMask {
        anchors.fill: corner
        source: corner
        maskSource: background
    }

    Item {
        id: top

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: bottom.top
        }

        Image {
            id: image

            source: giftCard.imageUrl
            width: 59*dp
            height: 40*dp
            sourceSize: Qt.size(2*width, 2*height)
            anchors {
                left: parent.left
                leftMargin: Consts.margin
                verticalCenter: parent.verticalCenter
            }
        }

        Text {
            text: giftCard.moneyStr
            font {
                pixelSize: Consts.fontNormal
                weight: Font.Bold
            }
            anchors {
                right: parent.right
                rightMargin: Consts.margin
                verticalCenter: parent.verticalCenter
            }
        }
    } // id: top

    Rectangle {
        id: bottom

        color: Colors.cardBottomSteam
        height: 42*dp
        radius: Consts.radius
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }

        Rectangle {
            color: bottom.color
            height: Consts.radius
            anchors {
                top: parent.top
                left: parent.left
                right: parent.right
            }
        }

        Row {
            anchors.centerIn: parent
            spacing: Consts.spacing

            Text {
                text: giftCard.creditsStr
                font {
                    pixelSize: Consts.fontNormal
                    weight: Font.Bold
                }
                color: Colors.textWhite
            }

            Text {
                text: qsTr("coins")
                font.pixelSize: Consts.fontNormal
                color: Colors.textGray
            }
        } // Row {
    } // Rectangle { id: bottom
}
