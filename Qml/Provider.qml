/// @author M. A. Serebrennikov
import QtQuick 2.12
import Sp 1.0

Item {
    width: parent.width
    height: title.height + listView.height + 2*Consts.marginMiddle

    Text {
        id: title

        text: provider.title
        color: Colors.text
        font {
            pixelSize: Consts.fontBig
            weight: Font.Bold
        }
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            leftMargin: Consts.marginMiddle
        }
    }

    ListView {
        id: listView

        delegate: GiftCard {}
        model: QSortFilterProxyModel {
            sourceModel: giftCardModel
        }
        orientation: Qt.Horizontal
        height: Consts.giftCardHeight
        leftMargin: Consts.marginMiddle
        spacing: Consts.marginMiddle

        anchors {
            top: title.bottom
            left: parent.left
            right: parent.right
            topMargin: Consts.margin
        }
    }

    GiftCardModel {
        id: giftCardModel
        provider: model.provider
    }
}
