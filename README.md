# Dithering Service

**Dithering in Graphics** is a technology that allows us to approximate colors with available ones.
In this task you have to distillate the image into two values - black and white, and still 
preserve the graphical idea.

## Example
1. ### Original
   ![](assets/original.jpeg)

2. ### Naive approach (threshold effect)
   ![](assets/not-dithered.jpeg)

3. ### Dithering
   ![](assets/dithered.jpg)

Let's compare them:

<table>
	<tr>
    	<td> <img src="assets/not-dithered.jpg"  alt="Not dithered picture"></td>
    	<td> <img src="assets/dithered.jpg"  alt="Dithered picture"></td>
	</tr> 
</table>

In both cases we use only two colors, but the quality of the picture on the right is definitely better. This effect is achieved through _error diffusion_.
**The error** is a difference between selected and closest from available colors (values). There are many diffusion algorithms, but this task focuses
on the most famous of them - the Floyd-Steinberg algorithm. The main advantage of this algorithm is good enough quality and speed, as the implementation
can use _bitwise operators_.

## Floyd-Steinberg Algorithm
Loop through image pixels, from up to down, from left to right. The error is calculated as follows:

- Let X be the current pixel, pn is a neighbour of X.

   |   |   |   |
   |---|---|---|
   |    | X  | p4 |
   | p1 | p2 | p3 |
   
- To calculate the error for X, find the closest value, either black or white, and find the difference
  between the original value and the closest one (`error = originalColor - suggestedColor`). Let X' be the error, so that for
  neighbouring pixels we add it, multiplied by the specified coefficient.

   |   |   |   |
   |---|---|---|
   |   | suggestedColor  |  p4 + X' * 7/16 |
   | p1 + X' * 3/16 | p2 + X' * 5/16 | p3 + X' * 1/16 |
   
Repeat the steps above for every pixel of the image.

## Requirements
Implement a RESTful service:
- Use port `8080` for your HTTP server
- Create the endpoint `/dither`. The image is sent by `POST` HTTP request, content type - `multipart/form-data`, parameter name - `image`
  - Store the processed images in the `images` directory on the server, preserving the same name and extension. Client must be able
    to look through the processed images from directory `images` using `images` endpoint (f.e, `http://localhost:8080/images/some-image.jpg`)


General requirements:
- Implement your own Floyd-Steinberg algorithm. You must not use the implementation from any other libraries. However, using libraries
  for other subtasks is allowed and is highly recommended. 
- **The compulsory** list of tools and libraries:
    - CMake v3.14+ 
    - boost/boost.beast v1.73+
- `build.sh` must build and run your project. You may edit other files as you wish, with regards to the other requirements

## Maintainer's guide

### Testing
#### Preconditions
- [ ] Install the compulsory list of tools and libraries.
#### Checklist
- [ ] Run `build.sh`. Observe no errors.
- [ ] Send a `.jpeg` or `.png` image using `curl`: 

       curl -F 'image=@<image>' localhost:8080/dither

    Observe response `200 OK` in your console.
    
- [ ] Go to `localhost:8080/images/<image>` from your browser. Observe the dithering effect on the image.
- [ ] Repeat steps 1-2 for another two or three images. Evaluate the quality of the algorithm, based on the following criteria:
  - [ ] The image can be quickly discerned
  - [ ] The image does not contain significant visual glitches (abnormal pixel clusters, extremely uneven shading etc.)
  - [ ] The image is not too dark, neither is too light compared to the source material.
- [ ] Send the same image twice, as specified in step 1. Obsereve response `200 OK` in your console.

### Code Review
- [ ] Used boost::asio, boost::beast
- [ ] No raw pointers are used
- [ ] Potential errors are wrapped in try-catch
- [ ] Header guards are present
