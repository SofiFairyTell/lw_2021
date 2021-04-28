package ru.bstu.it32.kurbatova.lab4;

import java.io.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Parser
{
    public void HtmlParser(String filePath, String replacement) throws IOException {
        BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath));
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter("result.html"));
        String patt = "<img.*?src?= ?['\\\"]([^'\\\"]*)['\\\"](.*?)(width.*?|height.*?|\\S)\\/";
        //String patt2 ="(?|(width.*?['\\\"]([^'\\\"]*)['\\\"])|(height.*?['\\\"]([^'\\\"]*)['\\\"]))";
        //Разбить паттерна три группы! Тогда  первой группе д.б. img + src, потом вставка наших значений и соединение со второй группой
        Pattern pattern = Pattern.compile(patt);

        Matcher matcher;

        String input = "";
        StringBuilder result = new StringBuilder();
        while ((input = bufferedReader.readLine()) != null) {
            matcher = pattern.matcher(input);
            int lenght = matcher.groupCount();
            if (matcher.find())
            {

                       if(matcher.group(2)=="")
                       {
                           //то есть ни ширины ни высоты нет
                           String pat = "<img.*?src?= ?['\\\"]([^'\\\"]*)['\\\"](.*?)\\/";
                           Pattern patte = Pattern.compile(pat);
                           matcher = patte.matcher(input);
                           if (matcher.find())
                           {
                               String group = matcher.group(2) + replacement;
                               input = input.replaceAll(matcher.group(2),group);
                               System.out.println(input);
                               result.append(input).append("\n");
                           }
                       }
                       else
                       {
                           String group = matcher.group(2) + replacement;
                           input = input.replaceAll(matcher.group(2)+matcher.group(3),group);
                           System.out.println(input);
                           result.append(input).append("\n");
                       }
            }
            else
            {
                result.append(input).append("\n");
            }
        }
        System.out.println(result);
        bufferedWriter.write(result.toString());
        bufferedWriter.close();
    }
}
