/*
    Nikita Tran
    CPSC 4160 2D Game Engine Construction
    Fall 2020
*/

#include "GameObject.h"

#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

GameObject::GameObject(){};
GameObject::~GameObject(){};

/*
    Wrapper for Sprite constructor: Creates a texture with the desired image file
    This needs to be called before doing anything else with the GameObject

    ren = renderer
    file = path of image file used for the sprite (example: "./spritesheet.png")
*/
void GameObject::Init(SDL_Renderer *ren, const char *file){
    renderer = ren;
    sprite = new Sprite(renderer, file);
    SDL_Rect temp{0,0,0,0};
    boxCollider = temp;
    alpha = 255;
}

void GameObject::Update(){};

/*
    Renders the sprite associated with this GameObject

    Parameters (taken from SDL documentation for SDL_RenderCopyEx):
    angle: An angle in degrees that indicates the rotation that will be applied to dstrect, rotating it in a clockwise direction
    center: a pointer to a point indicating the point around which dstrect will be rotated (if NULL, rotation will be done around dstrect.w/2, dstrect.h/2)
    flip: a SDL_RendererFlip value (SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL) stating which flipping actions should be performed on the texture
*/
void GameObject::Render(double angle, SDL_Point* center, SDL_RendererFlip flip){
    SDL_RenderCopyEx(renderer, sprite->GetTexture(), sprite->GetSrcRect(), sprite->GetScreenRect(), angle, center, flip);
}

void GameObject::Render(){
    SDL_RenderCopy(renderer, sprite->GetTexture(), sprite->GetSrcRect(), sprite->GetScreenRect());
}

void GameObject::RenderBoxCollider(){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_RenderFillRect(renderer, &boxCollider);
}

Sprite* GameObject::GetSprite(){ return sprite; }

ObjType GameObject::GetType(){ return objType; }

SDL_Rect GameObject::GetBoxCollider(){ return boxCollider; }

int GameObject::GetAlpha(){ return alpha; }

// Move x position of object by i pixels on screen
void GameObject::MoveX(int i){
    int x = sprite->GetX() + i;
    sprite->SetX(x);
}

// Move y position of object by i pixels on screen
void GameObject::MoveY(int i){
    int y = sprite->GetY() + i;
    sprite->SetY(y);
}

void GameObject::SetBoxCollider(int x, int y, int w, int h){
    boxCollider.x = x;
    boxCollider.y = y;
    boxCollider.w = w;
    boxCollider.h = h;
}

void GameObject::SetBoxCollider(SDL_Rect *r){
    boxCollider.x = r->x;
    boxCollider.y = r->y;
    boxCollider.w = r->w;
    boxCollider.h = r->h;
}

void GameObject::SetBoxColliderPos(int x, int y){
    boxCollider.x = x;
    boxCollider.y = y;
}

/*
    param:
        a = a number from [0, 255]; 255 = opaque, 0 = transparent, 1-254 = translucent
*/
void GameObject::SetAlpha(int a){
    if(a <= 0) alpha = 0;
    else if (a > 255) alpha = 255;
    else alpha = a;
}

/*
    This function increment/decrements alpha value by var
*/
void GameObject::ChangeAlpha(int var){
    alpha += var;
    if(alpha <= 0) alpha = 0;
    if (alpha > 255) alpha = 255;
}
