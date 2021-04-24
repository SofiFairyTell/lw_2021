
<?php
function titleChange(): string
{
    if (stripos($_SERVER['REQUEST_URI'], 'travelblog')) 
    {
        return 'TravelBlog';
    } 
    else 
        if (stripos($_SERVER['REQUEST_URI'], 'lifehack')) 
        {
            return 'Лайфхаки';
        } 
        else 
            if (stripos($_SERVER['REQUEST_URI'], 'contacts')) 
            {
            return 'Контакты';
            } 
            else 
                if (stripos($_SERVER['REQUEST_URI'], 'aboutus')) 
                {
                return 'О нас';
                } 
                else 
                {
                    return 'TravelBlog';
                }

}