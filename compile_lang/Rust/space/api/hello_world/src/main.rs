use axum::{Json, routing::get};

#[derive(serde::Serialize)]
struct Message {
    txt : String,
}

#[tokio::main]
async fn main() -> Result<(), Box<dyn std::error::Error>> {
    let app = axum::Router::new()
    .route("/", get(|| async {"This is root"}))
    .route("/hello", get(get_hello_message));

    let listener = tokio::net::TcpListener::bind("0.0.0.0:3000").await?;
    
    axum::serve(listener, app).await?;
    Ok(())
}

async fn get_hello_message() -> Json<Message> {
    Json(
        Message {
            txt : "Hello World!".to_string()
        }
    )
}