package ru.bstu.it32.kurbatova.lab5;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.ArrayList;

public class ParseDOM
{
    private final String filePath;
    public ParseDOM(String filepath)
    {
        this.filePath = filepath;
    }

    public void getDOMNodes() {
        File xmlFile = new File(this.filePath);
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder;
        try {
            builder = factory.newDocumentBuilder();
            Document document = builder.parse(xmlFile);
            // теперь XML полностью загружен в память
            //вернули корневой элемент документа и нормализовали
            document.getDocumentElement().normalize();
            System.out.println("Корневой элемент: " + document.getDocumentElement().getNodeName());
            // получаем узлы с именем Language
            NodeList nodeList = document.getElementsByTagName("Language");
            for (int i = 0; i < nodeList.getLength(); i++) {
                Node node = nodeList.item(i);
                // если узел является элементом
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element element = (Element) node;
                    System.out.println("\nЭлемент "+element.getNodeName());

                    // получаем список дочерних
                    NodeList childNodesList = element.getChildNodes();
                    for (int j = 0; j < childNodesList.getLength(); j++) {
                        Node childNode = childNodesList.item(j);
                        // если узел является элементом
                        if (childNode.getNodeType() == Node.ELEMENT_NODE) {
                            System.out.println(childNode.getNodeName()+": "+ childNode.getTextContent());
                        }
                    }
                }
            }
        } catch (Exception exc) {
            exc.printStackTrace();
        }
    }

    public void setDomNodes(ArrayList<Eventlist> eventslist) {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder;
        try {
            builder = factory.newDocumentBuilder();
            Document doc = builder.newDocument();// создаем пустой объект Document
            // создаем корневой элемент
            Element rootElement = doc.createElement("Eventlists");
            doc.appendChild(rootElement);
            // добавляем корневой элемент в объект Document
            for(int i = 0; i < eventslist.size(); i++){
                rootElement.appendChild(getEvent(doc, eventslist.get(i).getId(), eventslist.get(i).getName(), eventslist.get(i).getType(),
                        eventslist.get(i).getDate_start(), eventslist.get(i).getDate_end(),
                        eventslist.get(i).getManager(), eventslist.get(i).getPlace()));
            }
            doc.getDocumentElement().normalize();
//            //создаем объект TransformerFactory для преобразования документа в файл
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            // установка параметров форматирования для красивого вывода
            transformer.setOutputProperty(OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
            //получение исходного кода готового документа
            DOMSource source = new DOMSource(doc);
            //создание объекта для записи - файл
            var prop = new ParseProperties();
            var catalog = prop.readCatalogRoot();
            StreamResult file = new StreamResult(new File(catalog + "\\file.xml"));

            //запись данных
           transformer.transform(source, file);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // метод для создания нового узла XML-файла
    private static Node getEvent(Document doc, int id, String event_name, String event_type, String date_start, String date_end,
                                 String manager, String place)
    {
        Element language = doc.createElement("Eventlist");
        language.setAttribute("id", id+""); // устанавливаем атрибут id
        // создаем элементы name и age
        language.appendChild(getLanguageElements(doc, "event_name", event_name));
        language.appendChild(getLanguageElements(doc, "event_type", event_type));
        language.appendChild(getLanguageElements(doc, "date_start", date_start));
        language.appendChild(getLanguageElements(doc, "date_end", date_end));
        language.appendChild(getLanguageElements(doc, "manager", manager));
        language.appendChild(getLanguageElements(doc, "place", place));
        return language;
    }

    // метод для создания одного узла
    private static Node getLanguageElements(Document doc, String name, String value) {
        Element node = doc.createElement(name);
        node.appendChild(doc.createTextNode(value));
        return node;
    }

}
