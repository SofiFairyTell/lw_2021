package ru.bstu.it32.kurbatova.lab5;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;

import javax.xml.stream.XMLOutputFactory;

import javax.xml.stream.XMLStreamWriter;


import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.io.File;
import java.io.FileOutputStream;

import java.util.ArrayList;
import java.util.Arrays;

public class ParseSAX
{
    protected String content;
    protected boolean flag = false;
    protected ArrayList<Eventlist> eventslist = new ArrayList<Eventlist>();
    protected String[] strMas = new String[6];
    protected Eventlist eventlist;


    private final DefaultHandler handler = new DefaultHandler()
    {
        String tag = "";
        String id = "";

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException
        {
            tag = qName;
            if (tag.equalsIgnoreCase("Eventlist"))
                id = attributes.getValue("id");
        }
        @Override
        public void characters(char ch[], int start, int length) throws SAXException {
            if (tag.equalsIgnoreCase("event_name")) {
                strMas[0] = new String(ch, start, length);
            } else if (tag.equalsIgnoreCase("event_type")) {
                strMas[1] = new String(ch, start, length);
            } else if (tag.equalsIgnoreCase("date_start")) {
                strMas[2] = new String(ch, start, length);
            } else if (tag.equalsIgnoreCase("date_end")) {
                strMas[3] = new String(ch, start, length);
            } else if (tag.equalsIgnoreCase("manager")) {
                strMas[4] = new String(ch, start, length);
            } else if (tag.equalsIgnoreCase("place")) {
                strMas[5] = new String(ch, start, length);
            }
                if (strMas[0] != null && strMas[1] != null &&  strMas[2] != null && strMas[3] != null && strMas[4] != null
                        && strMas[5] != null && !id.equals(""))
            {
                Eventlist eventlist = new Eventlist(Integer.parseInt(id), strMas[0], strMas[1],strMas[2],strMas[3],
                       strMas[4], strMas[5]);
                Arrays.fill(strMas, null);
                eventslist.add(eventlist);
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            tag = "";
        }
    };

    private final DefaultHandler handlerSearch = new DefaultHandler() {
        String tag = "";
        String id = "";

        @Override
        public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {
            tag = qName;
            if (tag.equalsIgnoreCase("Eventlist"))
                id = attributes.getValue("id");
        }

        @Override
        public void characters(char ch[], int start, int length) throws SAXException {
            if (id.equalsIgnoreCase(content)) {
                if (tag.equalsIgnoreCase("event_name") && strMas[0] == null) {
                    strMas[0] = new String(ch, start, length);
                } else if (tag.equalsIgnoreCase("event_type") && strMas[1] == null) {
                    strMas[1] = new String(ch, start, length);
                } else if (tag.equalsIgnoreCase("date_start") && strMas[2] == null) {
                    strMas[2] = new String(ch, start, length);
                } else if (tag.equalsIgnoreCase("date_end") && strMas[3] == null) {
                    strMas[3] = new String(ch, start, length);
                } else if (tag.equalsIgnoreCase("manager") && strMas[4] == null) {
                    strMas[4] = new String(ch, start, length);
                } else if (tag.equalsIgnoreCase("place") && strMas[5] == null) {
                    strMas[5] = new String(ch, start, length);
                }
                if (strMas[0] != null && strMas[1] != null&& strMas[2] != null && strMas[3] != null&& strMas[4] != null && strMas[5] != null && !id.equals("")) {
                   eventlist = new Eventlist(Integer.parseInt(id), strMas[0], strMas[1], strMas[2],strMas[3],strMas[4], strMas[5]);
                }
            }
        }

        @Override
        public void endElement(String uri, String localName, String qName) throws SAXException {
            if (tag.equalsIgnoreCase(""))
                flag = false;
            if (tag.equalsIgnoreCase("event_name") ||
                    tag.equalsIgnoreCase("event_type") ||
                    tag.equalsIgnoreCase("date_start") ||
                    tag.equalsIgnoreCase("date_end") ||
                    tag.equalsIgnoreCase("manager") ||
                    tag.equalsIgnoreCase("place"))
                tag = "";
        }
    };

    public Eventlist searchSaxDocument(String filePath, String content) {
        try {
            SAXParserFactory factory = SAXParserFactory.newInstance();
            SAXParser saxParser = factory.newSAXParser();
            this.content = content;
            saxParser.parse(new File(filePath), handlerSearch);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return eventlist;
    }

    public ArrayList<Eventlist> readerSaxDocument(String filePath) {
        try {
            SAXParserFactory factory = SAXParserFactory.newInstance();
            SAXParser saxParser = factory.newSAXParser();
            saxParser.parse(new File(filePath), this.handler);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return this.eventslist;
    }

    //В качестве аргумента принимает путь файла, в который нужно записать
    public void writeSaxDocument(String filePath) {
        try {
            XMLOutputFactory xmlOutputFactory = XMLOutputFactory.newFactory();
            XMLStreamWriter writer = xmlOutputFactory.createXMLStreamWriter(new FileOutputStream(filePath));
            writer.writeStartDocument();
            writer.writeCharacters("\n");
            writer.writeStartElement("root");
            writer.writeCharacters("\n");
            writer.writeStartElement("font");
            writer.writeAttribute("id", "1");
            writer.writeCharacters("TimesNewRoman\n");
            writer.writeEndElement();
            writer.writeEndElement();
            writer.writeEndDocument();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
