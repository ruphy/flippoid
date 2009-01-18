#include "flippoid.h"
#include <QPainter>
#include <QFontMetrics>
#include <QSizeF>
#include <KLocale>

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QLabel>

#include <KLineEdit>

#include <Plasma/Label>
#include <Plasma/LineEdit>
#include <Plasma/Svg>
#include <Plasma/Theme>

flippoid::flippoid(QObject *parent, const QVariantList &args)
    : Plasma::PopupApplet(parent, args),
    m_w(0);
{
    // this will get us the standard applet background, for free!
    setBackgroundHints(DefaultBackground);
    
    setPopupIcon("format-text-direction-rtl"); // TODO: draw an icon

    setHasConfigurationInterface(true);  
    resize(200, 200);
}


flippoid::~flippoid()
{
    if (hasFailedToLaunch()) {
        // Do some cleanup here
    } else {
        // Save settings
    }
}

void flippoid::init()
{
    // A small demonstration of the setFailedToLaunch function
    if (m_icon.isNull()) {
        setFailedToLaunch(true, i18n("No world to say hello"));
    }
}

QGraphicsWidget *flippoid::graphicsWidget()
{
    if (!m_w) {
        m_w = new QGraphicsWidget(this);
        QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, m_w);
        
        m_lineEdit = new Plasma::LineEdit(m_w);
        m_flippedText = new Plasma::Label(m_w);
    
        connect(m_lineEdit, SIGNAL(editingFinished()), this, SLOT(flipText()));
        
        m_lineEdit->nativeWidget()->setClickMessage(i18n("Write here the text you want to flip..."));
        m_flippedText->setText(i18n("Press Enter to see the results."));
        m_flippedText->nativeWidget()->setTextInteractionFlags(Qt::TextSelectableByMouse);
        
        layout->addItem(m_lineEdit);
        layout->addItem(m_flippedText);
        
        m_w->setLayout(layout);
    }
    
    return m_w;
}

QChar flippoid::inverseChar(const QChar &c)
{
    QMap<QChar, QChar> flipMap;
    
    // prepend a couple of missing ones...
    flipMap['u'] = 'n';
    flipMap['p'] = 'd';
    flipMap['q'] = 'b'; 
    flipMap['>'] = '<';

    //the two alternatives for l
//     flipMap['l'] = '|';
    flipMap[0x006C] = 0x0283;
    
    // the rest has been found on several websites, I looked for the unicode code.
    flipMap[0x0021] = 0x00A1;
    flipMap[0x0022] = 0x201E;
    flipMap[0x0026] = 0x214B;
    flipMap[0x0027] = 0x002C;
    flipMap[0x0028] = 0x0029;
    flipMap[0x002E] = 0x02D9;
    flipMap[0x0033] = 0x0190;
    flipMap[0x0034] = 0x152D;
    flipMap[0x0036] = 0x0039;
    flipMap[0x0037] = 0x2C62;
    flipMap[0x003B] = 0x061B;
    flipMap[0x003C] = 0x003E;
    flipMap[0x003F] = 0x00BF;
    flipMap[0x0041] = 0x2200;
    flipMap[0x0042] = 0x10412;
    flipMap[0x0043] = 0x2183;
    flipMap[0x0044] = 0x25D6;
    flipMap[0x0045] = 0x018E;
    flipMap[0x0046] = 0x2132;
    flipMap[0x0047] = 0x2141;
    flipMap[0x004A] = 0x017F;
    flipMap[0x004B] = 0x22CA;
    flipMap[0x004C] = 0x2142;
    flipMap[0x004D] = 0x0057;
    flipMap[0x004E] = 0x1D0E;
    flipMap[0x0050] = 0x0500;
    flipMap[0x0051] = 0x038C;
    flipMap[0x0052] = 0x1D1A;
    flipMap[0x0054] = 0x22A5;
    flipMap[0x0055] = 0x2229;
    flipMap[0x0056] = 0x1D27;
    flipMap[0x0059] = 0x2144;
    flipMap[0x005B] = 0x005D;
    flipMap[0x005F] = 0x203E;
    flipMap[0x0061] = 0x0250;
    flipMap[0x0062] = 0x0071;
    flipMap[0x0063] = 0x0254;
    flipMap[0x0064] = 0x0070;
    flipMap[0x0065] = 0x01DD;
    flipMap[0x0066] = 0x025F;
    flipMap[0x0067] = 0x0183;
    flipMap[0x0068] = 0x0265;
    flipMap[0x0069] = 0x0131;
    flipMap[0x006A] = 0x027E;
    flipMap[0x006B] = 0x029E;
    flipMap[0x006D] = 0x026F;
    flipMap[0x006E] = 0x0075;
    flipMap[0x0072] = 0x0279;
    flipMap[0x0074] = 0x0287;
    flipMap[0x0076] = 0x028C;
    flipMap[0x0077] = 0x028D;
    flipMap[0x0079] = 0x028E;
    flipMap[0x007B] = 0x007D;
    flipMap[0x203F] = 0x2040;
    flipMap[0x2045] = 0x2046;
    flipMap[0x2234] = 0x2235;
    
    QChar d;

    if (flipMap.contains(c)) {
        d = flipMap[c];
    } else {
        d = c;
    }

    return d;
}

void flippoid::flipText()
{
    QString s = m_lineEdit->text();
    
    s = s.toLower(); // Uppercase letters seem to have some bugs...
    
    QString flipped;
    for (int i = 0; i < s.size(); i++) {
        flipped[i] = inverseChar(s.at((s.size()-1)-i));
    }
    
    m_flippedText->setText(flipped);
    
//     kDebug() << flipped;
}

#include "flippoid.moc"
