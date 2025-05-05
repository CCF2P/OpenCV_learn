#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>   // содержит функции для отображения изображений в графическом окне
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

// using namespace std; // пространство имен std (чтобы не писать std::...)
// using namespace cv; // пространство имен cv (чтобы не писать cv::...)

/*
* example1 - процедура, которая содержит простой пример для работы
* с изображениями. Она показывает как открыть изображение и вывести его
* на экран.
*/
void example1()
{
	// переменная path содержить путь к файлу-картинке
	std::string path = "E:/OpenCV_learn/Resources/Images/Test.png";

	/*
	cv::Mat - класс для хранения изображений в openCV с двумя частями данных:
	1 - заголовком матрицы (содержащим такую ​​информацию, как размер матрицы,
	метод, используемый для хранения, адрес, по которому хранится матрица, и т. д.)
	2 - указателем на матрицу, содержащую значения каждого пикселя изображения
	(под значением пикселя понимается три числа BGR (blue, green, red), которые и задают цвет пикселя).

	Причем важно помнить, что в openCV значение пикселя - BGR, а в других библиотеках - RGB (red,
	green, blue).
	*/
	cv::Mat img, img1;
	
	/*
	imread() - функция, для считывания изображения из файла.

	Параметры:
	1 - string filename - путь к файлу, в котором хранится изображение. Поддерживает следующие форматы
	изображений: png, jpeg, jpg, gif и т.д. НО!!! Есть особенности, которые зависят от ОС и версии openCV.
	2 - int flags - флаги (специальные значения) для определения каким образом
	будет считываться изображение, например:
	IMREAD_UNCHANGED - возвращает изображение таким какое оно есть (с альфа каналом).
	IMREAD_GRAYSCALE - всегда конвертирует изображение в одноканальное серое изображение.
	IMREAD_COLOR_BGR - всегда конвертирует изображение в 3-х канальное BGR цветное изображение.
	IMREAD_ANYCOLOR - считывает изображение в том формате, в котором может.
	IMREAD_COLOR_RGB - всегда конверитует изображение в 3-х канальное RGB цветное изображение.
	И другие... (смотри сайт с документацией)
	*/
	img = cv::imread(path); // Без флага
	img1 = cv::imread(path, cv::IMREAD_GRAYSCALE); // С флагом

	/*
	imshow() - функция, которая создает графическое окно с такой же шириной и высотой,
	как у изображение, которое передается в функцию.
	 
	Параметры:
	1 - string winname - графического окна, если необходимо создать несколько окон, то
	необходимо их по разному называть, т.к. окна с одним и тем же названием считаются
	как одно.
	2 - InputArray mat - изображение, которе необходимо нарисовать в графическом окне.
	*/
	cv::imshow("Image", img);

	/*
	cv::waitKey() - функция для задержки графического окна. Если ее убрать, то
	результат не будет задерживаться на экране компьютера.
	0 - программа ждет нажатия клавиш или закрытия окна.
	число > 0 - время в миллисекундах, через сколько закроется окно.
	*/
	cv::waitKey(0);
}

/*
example2 - процедура, которая содержит пример для изменения изображения.
*/
void example2()
{
	std::string path = "E:/OpenCV_learn/Resources/Images/Test.png";
	cv::Mat img = cv::imread(path);

	// Переменные для хранения измененных изображений
	cv::Mat imgGray, imgBlur, imgThresh;

	/*
	cvtColor() - функция, которая конвертирует изображение из одного
	цветого пространства в другое (например цветное сделать черно-белым).

	Параметры:
	1 - InputArray src - изображение, которые необходимо конвертировать
	2 - OutputArray dst - изображение, которые будет в себе хранить уже измененное
	исходное изображение.
	3 - int code - число, которе определяет в какое цветовое пространство конвертировать,
	например:
	COLOR_BGR2BGRA - перевести изображение из BGR в BGRA, т.е. добавать альфа канал.
	COLOR_RGB2RGBA - аналогично COLOR_BGR2BGRA, только для RGB.
	COLOR_BGRA2BGR - перевести изображение из BGRA в BGR, т.е. удалить альфа канал.
	COLOR_RGBA2RGB - аналогично COLOR_BGRA2BGR, только для RGB.
	COLOR_RGB2GRAY - перевести изображение из RGB в GRAY, т.е. перекрасить изображение оттенками серого.
	COLOR_BGR2GRAY - аналогично COLOR_RGB2GRAY, только для BGR.
	И другие... (смотри сайт с документацией)
	*/
	cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

	GaussianBlur(imgGray, imgBlur, cv::Size(7, 7), 5, 0);

	cv::threshold(imgBlur, imgThresh, 100, 200, cv::THRESH_BINARY);


	cv::imshow("Grayscale", imgGray);
	cv::imshow("GaussianBlur", imgBlur);
}

void example3()
{
	cv::VideoCapture videoCap(0);
	cv::CascadeClassifier facedetect;
	cv::Mat img;
	facedetect.load("E:/OpenCV_learn/Resources/haarcascade_frontalface_default.xml");

	while (true)
	{
		videoCap.read(img);
		std::vector<cv::Rect> faces;

		facedetect.detectMultiScale(img, faces, 1.3, 5);

		for (int i = 0; i < faces.size(); ++i)
		{
			rectangle(img, faces[i].tl(),
					  faces[i].br(), cv::Scalar(50, 50, 255), 3);
			rectangle(img, cv::Point(0, 0), cv::Point(250, 70),
					  cv::Scalar(50, 50, 255), cv::FILLED);
			putText(img, std::to_string(faces.size()) + " Face Found",
					cv::Point(10, 40), cv::FONT_HERSHEY_DUPLEX, 1,
					cv::Scalar(255, 255, 255), 1);
		}


		imshow("Frame", img);
		cv::waitKey(1);
	}
}

int main(int argc, char* argv[])
{
	/*
	cv::Mat img(256, 256, CV_8UC3);

	cv::circle(img, cv::Point(128, 128), 64, cv::Scalar(0, 0, 0), 3);
	cv::rectangle(img, cv::Rect(64, 128, 128, 128), cv::Scalar(255, 0, 255), 3);

	imshow("Image", img);

	cv::waitKey(0);
	*/
	return 0;
}