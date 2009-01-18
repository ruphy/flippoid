// Here we avoid loading the header multiple times
#ifndef FLIPPOID_HEADER
#define FLIPPOID_HEADER
// We need the Plasma Applet headers
#include <KIcon>

#include <Plasma/PopupApplet>
#include <Plasma/Svg>

namespace Plasma {
    class Label;
    class LineEdit;
}

class QSizeF;
class QChar;

// Define our plasma Applet
class flippoid : public Plasma::PopupApplet
{
    Q_OBJECT
    public:
        // Basic Create/Destroy
        flippoid(QObject *parent, const QVariantList &args);
        ~flippoid();

        // The paintInterface procedure paints the applet to screen
//         void paintInterface(QPainter *painter,
//                 const QStyleOptionGraphicsItem *option,
//                 const QRect& contentsRect);

        QGraphicsWidget *graphicsWidget();

        void init();

    public Q_SLOTS:
        void flipText();

    private:
        QChar inverseChar(const QChar &c);

        Plasma::Svg m_svg;
        QGraphicsWidget *m_w;
        Plasma::LineEdit *m_lineEdit;
        Plasma::Label *m_flippedText;
        KIcon m_icon;
};
 
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_APPLET(flippoid, flippoid)
#endif
